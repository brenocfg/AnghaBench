#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct Curl_sh_entry {unsigned int action; int /*<<< orphan*/  transfers; int /*<<< orphan*/  socketp; int /*<<< orphan*/  users; scalar_t__ readers; scalar_t__ writers; } ;
struct Curl_multi {int /*<<< orphan*/  sockhash; int /*<<< orphan*/  socket_userp; int /*<<< orphan*/  (* socket_cb ) (struct Curl_easy*,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct Curl_easy {int numsocks; scalar_t__* sockets; unsigned int* actions; } ;
typedef  scalar_t__ curl_socket_t ;
typedef  int /*<<< orphan*/  CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLM_OK ; 
 int /*<<< orphan*/  CURLM_OUT_OF_MEMORY ; 
 unsigned int CURL_POLL_IN ; 
 unsigned int CURL_POLL_NONE ; 
 unsigned int CURL_POLL_OUT ; 
 unsigned int CURL_POLL_REMOVE ; 
 scalar_t__ CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  Curl_hash_add (int /*<<< orphan*/ *,char*,int,struct Curl_easy*) ; 
 scalar_t__ Curl_hash_delete (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  DEBUGASSERT (int /*<<< orphan*/ *) ; 
 int FALSE ; 
 unsigned int GETSOCK_READSOCK (int) ; 
 unsigned int GETSOCK_WRITESOCK (int) ; 
 int MAX_SOCKSPEREASYHANDLE ; 
 int TRUE ; 
 int /*<<< orphan*/  memcpy (int*,...) ; 
 unsigned int multi_getsock (struct Curl_easy*,scalar_t__*) ; 
 struct Curl_sh_entry* sh_addentry (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sh_delentry (struct Curl_sh_entry*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct Curl_sh_entry* sh_getentry (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct Curl_easy*,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct Curl_easy*,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLMcode singlesocket(struct Curl_multi *multi,
                              struct Curl_easy *data)
{
  curl_socket_t socks[MAX_SOCKSPEREASYHANDLE];
  int i;
  struct Curl_sh_entry *entry;
  curl_socket_t s;
  int num;
  unsigned int curraction;
  int actions[MAX_SOCKSPEREASYHANDLE];

  for(i = 0; i< MAX_SOCKSPEREASYHANDLE; i++)
    socks[i] = CURL_SOCKET_BAD;

  /* Fill in the 'current' struct with the state as it is now: what sockets to
     supervise and for what actions */
  curraction = multi_getsock(data, socks);

  /* We have 0 .. N sockets already and we get to know about the 0 .. M
     sockets we should have from now on. Detect the differences, remove no
     longer supervised ones and add new ones */

  /* walk over the sockets we got right now */
  for(i = 0; (i< MAX_SOCKSPEREASYHANDLE) &&
        (curraction & (GETSOCK_READSOCK(i) | GETSOCK_WRITESOCK(i)));
      i++) {
    unsigned int action = CURL_POLL_NONE;
    unsigned int prevaction = 0;
    unsigned int comboaction;
    bool sincebefore = FALSE;

    s = socks[i];

    /* get it from the hash */
    entry = sh_getentry(&multi->sockhash, s);

    if(curraction & GETSOCK_READSOCK(i))
      action |= CURL_POLL_IN;
    if(curraction & GETSOCK_WRITESOCK(i))
      action |= CURL_POLL_OUT;

    actions[i] = action;
    if(entry) {
      /* check if new for this transfer */
      int j;
      for(j = 0; j< data->numsocks; j++) {
        if(s == data->sockets[j]) {
          prevaction = data->actions[j];
          sincebefore = TRUE;
          break;
        }
      }
    }
    else {
      /* this is a socket we didn't have before, add it to the hash! */
      entry = sh_addentry(&multi->sockhash, s);
      if(!entry)
        /* fatal */
        return CURLM_OUT_OF_MEMORY;
    }
    if(sincebefore && (prevaction != action)) {
      /* Socket was used already, but different action now */
      if(prevaction & CURL_POLL_IN)
        entry->readers--;
      if(prevaction & CURL_POLL_OUT)
        entry->writers--;
      if(action & CURL_POLL_IN)
        entry->readers++;
      if(action & CURL_POLL_OUT)
        entry->writers++;
    }
    else if(!sincebefore) {
      /* a new user */
      entry->users++;
      if(action & CURL_POLL_IN)
        entry->readers++;
      if(action & CURL_POLL_OUT)
        entry->writers++;

      /* add 'data' to the transfer hash on this socket! */
      if(!Curl_hash_add(&entry->transfers, (char *)&data, /* hash key */
                        sizeof(struct Curl_easy *), data))
        return CURLM_OUT_OF_MEMORY;
    }

    comboaction = (entry->writers? CURL_POLL_OUT : 0) |
      (entry->readers ? CURL_POLL_IN : 0);

    /* socket existed before and has the same action set as before */
    if(sincebefore && (entry->action == comboaction))
      /* same, continue */
      continue;

    if(multi->socket_cb)
      multi->socket_cb(data, s, comboaction, multi->socket_userp,
                       entry->socketp);

    entry->action = comboaction; /* store the current action state */
  }

  num = i; /* number of sockets */

  /* when we've walked over all the sockets we should have right now, we must
     make sure to detect sockets that are removed */
  for(i = 0; i< data->numsocks; i++) {
    int j;
    bool stillused = FALSE;
    s = data->sockets[i];
    for(j = 0; j < num; j++) {
      if(s == socks[j]) {
        /* this is still supervised */
        stillused = TRUE;
        break;
      }
    }
    if(stillused)
      continue;

    entry = sh_getentry(&multi->sockhash, s);
    /* if this is NULL here, the socket has been closed and notified so
       already by Curl_multi_closed() */
    if(entry) {
      int oldactions = data->actions[i];
      /* this socket has been removed. Decrease user count */
      entry->users--;
      if(oldactions & CURL_POLL_OUT)
        entry->writers--;
      if(oldactions & CURL_POLL_IN)
        entry->readers--;
      if(!entry->users) {
        if(multi->socket_cb)
          multi->socket_cb(data, s, CURL_POLL_REMOVE,
                           multi->socket_userp,
                           entry->socketp);
        sh_delentry(entry, &multi->sockhash, s);
      }
      else {
        /* still users, but remove this handle as a user of this socket */
        if(Curl_hash_delete(&entry->transfers, (char *)&data,
                            sizeof(struct Curl_easy *))) {
          DEBUGASSERT(NULL);
        }
      }
    }
  } /* for loop over numsocks */

  memcpy(data->sockets, socks, num*sizeof(curl_socket_t));
  memcpy(data->actions, actions, num*sizeof(int));
  data->numsocks = num;
  return CURLM_OK;
}