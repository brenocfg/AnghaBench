#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connectdata {int /*<<< orphan*/ * sock; struct Curl_easy* data; } ;
struct TYPE_3__ {char* path; char* query; } ;
struct TYPE_4__ {TYPE_1__ up; } ;
struct Curl_easy {TYPE_2__ state; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENTWRITE_HEADER ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURLE_SEND_ERROR ; 
 scalar_t__ Curl_client_write (struct connectdata*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ Curl_sendf (int /*<<< orphan*/ ,struct connectdata*,char*) ; 
 int /*<<< orphan*/  Curl_setup_transfer (struct Curl_easy*,size_t,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ Curl_urldecode (struct Curl_easy*,char*,int /*<<< orphan*/ ,char**,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ Curl_write (struct connectdata*,int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  DEBUGASSERT (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 size_t FIRSTSOCKET ; 
 scalar_t__ SOCKET_WRITABLE (int /*<<< orphan*/ ,int) ; 
 int TRUE ; 
 char* aprintf (char*,char*,char*) ; 
 int curlx_uztosz (size_t) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static CURLcode gopher_do(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  curl_socket_t sockfd = conn->sock[FIRSTSOCKET];
  char *gopherpath;
  char *path = data->state.up.path;
  char *query = data->state.up.query;
  char *sel = NULL;
  char *sel_org = NULL;
  ssize_t amount, k;
  size_t len;

  *done = TRUE; /* unconditionally */

  /* path is guaranteed non-NULL */
  DEBUGASSERT(path);

  if(query)
    gopherpath = aprintf("%s?%s", path, query);
  else
    gopherpath = strdup(path);

  if(!gopherpath)
    return CURLE_OUT_OF_MEMORY;

  /* Create selector. Degenerate cases: / and /1 => convert to "" */
  if(strlen(gopherpath) <= 2) {
    sel = (char *)"";
    len = strlen(sel);
    free(gopherpath);
  }
  else {
    char *newp;

    /* Otherwise, drop / and the first character (i.e., item type) ... */
    newp = gopherpath;
    newp += 2;

    /* ... and finally unescape */
    result = Curl_urldecode(data, newp, 0, &sel, &len, FALSE);
    free(gopherpath);
    if(result)
      return result;
    sel_org = sel;
  }

  /* We use Curl_write instead of Curl_sendf to make sure the entire buffer is
     sent, which could be sizeable with long selectors. */
  k = curlx_uztosz(len);

  for(;;) {
    result = Curl_write(conn, sockfd, sel, k, &amount);
    if(!result) { /* Which may not have written it all! */
      result = Curl_client_write(conn, CLIENTWRITE_HEADER, sel, amount);
      if(result)
        break;

      k -= amount;
      sel += amount;
      if(k < 1)
        break; /* but it did write it all */
    }
    else
      break;

    /* Don't busyloop. The entire loop thing is a work-around as it causes a
       BLOCKING behavior which is a NO-NO. This function should rather be
       split up in a do and a doing piece where the pieces that aren't
       possible to send now will be sent in the doing function repeatedly
       until the entire request is sent.

       Wait a while for the socket to be writable. Note that this doesn't
       acknowledge the timeout.
    */
    if(SOCKET_WRITABLE(sockfd, 100) < 0) {
      result = CURLE_SEND_ERROR;
      break;
    }
  }

  free(sel_org);

  if(!result)
    /* We can use Curl_sendf to send the terminal \r\n relatively safely and
       save allocing another string/doing another _write loop. */
    result = Curl_sendf(sockfd, conn, "\r\n");
  if(result) {
    failf(data, "Failed sending Gopher request");
    return result;
  }
  result = Curl_client_write(conn, CLIENTWRITE_HEADER, (char *)"\r\n", 2);
  if(result)
    return result;

  Curl_setup_transfer(data, FIRSTSOCKET, -1, FALSE, -1);
  return CURLE_OK;
}