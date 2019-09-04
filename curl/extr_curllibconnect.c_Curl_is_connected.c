#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int timediff_t ;
struct curltime {int dummy; } ;
struct TYPE_20__ {char* name; } ;
struct TYPE_19__ {char* name; } ;
struct TYPE_18__ {scalar_t__ conn_to_host; scalar_t__ httpproxy; scalar_t__ socksproxy; void** tcpconnect; scalar_t__ tcp_fastopen; } ;
struct TYPE_16__ {char* name; } ;
struct TYPE_17__ {TYPE_5__ host; } ;
struct TYPE_14__ {char* name; } ;
struct TYPE_15__ {TYPE_3__ host; } ;
struct connectdata {scalar_t__* tempsock; scalar_t__ timeoutms_per_addr; scalar_t__* sock; int /*<<< orphan*/  port; TYPE_9__ host; TYPE_8__ conn_to_host; TYPE_7__ bits; TYPE_6__ http_proxy; TYPE_4__ socks_proxy; TYPE_10__** tempaddr; TYPE_10__* ip_addr; int /*<<< orphan*/  connecttime; struct Curl_easy* data; } ;
struct TYPE_13__ {int os_errno; } ;
struct TYPE_12__ {scalar_t__ happy_eyeballs_timeout; } ;
struct Curl_easy {TYPE_2__ state; TYPE_1__ set; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_11__ {int /*<<< orphan*/ * ai_next; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_COULDNT_CONNECT ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OPERATION_TIMEDOUT ; 
 int CURL_CSELECT_ERR ; 
 int CURL_CSELECT_OUT ; 
 scalar_t__ CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  Curl_closesocket (struct connectdata*,scalar_t__) ; 
 scalar_t__ Curl_connected_proxy (struct connectdata*,int) ; 
 struct curltime Curl_now () ; 
 int /*<<< orphan*/  Curl_pgrsTime (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_printable_address (TYPE_10__*,char*,int) ; 
 int /*<<< orphan*/  Curl_strerror (int,char*,int) ; 
 scalar_t__ Curl_timediff (struct curltime,int /*<<< orphan*/ ) ; 
 int Curl_timeleft (struct Curl_easy*,struct curltime*,void*) ; 
 int /*<<< orphan*/  Curl_updateconninfo (struct connectdata*,scalar_t__) ; 
 int /*<<< orphan*/  Curl_verboseconnect (struct connectdata*) ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 int ETIMEDOUT ; 
 int FALSE ; 
 int FIRSTSOCKET ; 
 int MAX_IPADR_LEN ; 
 int SECONDARYSOCKET ; 
 int /*<<< orphan*/  SET_SOCKERRNO (int) ; 
 int SOCKET_WRITABLE (scalar_t__,int /*<<< orphan*/ ) ; 
 int STRERROR_LEN ; 
 int /*<<< orphan*/  TIMER_CONNECT ; 
 void* TRUE ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,...) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,...) ; 
 scalar_t__ trynextip (struct connectdata*,int,int) ; 
 scalar_t__ verifyconnect (scalar_t__,int*) ; 

CURLcode Curl_is_connected(struct connectdata *conn,
                           int sockindex,
                           bool *connected)
{
  struct Curl_easy *data = conn->data;
  CURLcode result = CURLE_OK;
  timediff_t allow;
  int error = 0;
  struct curltime now;
  int rc;
  int i;

  DEBUGASSERT(sockindex >= FIRSTSOCKET && sockindex <= SECONDARYSOCKET);

  *connected = FALSE; /* a very negative world view is best */

  if(conn->bits.tcpconnect[sockindex]) {
    /* we are connected already! */
    *connected = TRUE;
    return CURLE_OK;
  }

  now = Curl_now();

  /* figure out how long time we have left to connect */
  allow = Curl_timeleft(data, &now, TRUE);

  if(allow < 0) {
    /* time-out, bail out, go home */
    failf(data, "Connection time-out");
    return CURLE_OPERATION_TIMEDOUT;
  }

  for(i = 0; i<2; i++) {
    const int other = i ^ 1;
    if(conn->tempsock[i] == CURL_SOCKET_BAD)
      continue;

#ifdef mpeix
    /* Call this function once now, and ignore the results. We do this to
       "clear" the error state on the socket so that we can later read it
       reliably. This is reported necessary on the MPE/iX operating system. */
    (void)verifyconnect(conn->tempsock[i], NULL);
#endif

    /* check socket for connect */
    rc = SOCKET_WRITABLE(conn->tempsock[i], 0);

    if(rc == 0) { /* no connection yet */
      error = 0;
      if(Curl_timediff(now, conn->connecttime) >= conn->timeoutms_per_addr) {
        infof(data, "After %ldms connect time, move on!\n",
              conn->timeoutms_per_addr);
        error = ETIMEDOUT;
      }

      /* should we try another protocol family? */
      if(i == 0 && conn->tempaddr[1] == NULL &&
         (Curl_timediff(now, conn->connecttime) >=
          data->set.happy_eyeballs_timeout)) {
        trynextip(conn, sockindex, 1);
      }
    }
    else if(rc == CURL_CSELECT_OUT || conn->bits.tcp_fastopen) {
      if(verifyconnect(conn->tempsock[i], &error)) {
        /* we are connected with TCP, awesome! */

        /* use this socket from now on */
        conn->sock[sockindex] = conn->tempsock[i];
        conn->ip_addr = conn->tempaddr[i];
        conn->tempsock[i] = CURL_SOCKET_BAD;
#ifdef ENABLE_IPV6
        conn->bits.ipv6 = (conn->ip_addr->ai_family == AF_INET6)?TRUE:FALSE;
#endif

        /* close the other socket, if open */
        if(conn->tempsock[other] != CURL_SOCKET_BAD) {
          Curl_closesocket(conn, conn->tempsock[other]);
          conn->tempsock[other] = CURL_SOCKET_BAD;
        }

        /* see if we need to do any proxy magic first once we connected */
        result = Curl_connected_proxy(conn, sockindex);
        if(result)
          return result;

        conn->bits.tcpconnect[sockindex] = TRUE;

        *connected = TRUE;
        if(sockindex == FIRSTSOCKET)
          Curl_pgrsTime(data, TIMER_CONNECT); /* connect done */
        Curl_updateconninfo(conn, conn->sock[sockindex]);
        Curl_verboseconnect(conn);

        return CURLE_OK;
      }
      infof(data, "Connection failed\n");
    }
    else if(rc & CURL_CSELECT_ERR)
      (void)verifyconnect(conn->tempsock[i], &error);

    /*
     * The connection failed here, we should attempt to connect to the "next
     * address" for the given host. But first remember the latest error.
     */
    if(error) {
      data->state.os_errno = error;
      SET_SOCKERRNO(error);
      if(conn->tempaddr[i]) {
        CURLcode status;
        char ipaddress[MAX_IPADR_LEN];
        char buffer[STRERROR_LEN];
        Curl_printable_address(conn->tempaddr[i], ipaddress, MAX_IPADR_LEN);
        infof(data, "connect to %s port %ld failed: %s\n",
              ipaddress, conn->port,
              Curl_strerror(error, buffer, sizeof(buffer)));

        conn->timeoutms_per_addr = conn->tempaddr[i]->ai_next == NULL ?
                                   allow : allow / 2;

        status = trynextip(conn, sockindex, i);
        if(status != CURLE_COULDNT_CONNECT
            || conn->tempsock[other] == CURL_SOCKET_BAD)
          /* the last attempt failed and no other sockets remain open */
          result = status;
      }
    }
  }

  if(result) {
    /* no more addresses to try */
    const char *hostname;
    char buffer[STRERROR_LEN];

    /* if the first address family runs out of addresses to try before
       the happy eyeball timeout, go ahead and try the next family now */
    if(conn->tempaddr[1] == NULL) {
      result = trynextip(conn, sockindex, 1);
      if(!result)
        return result;
    }

    if(conn->bits.socksproxy)
      hostname = conn->socks_proxy.host.name;
    else if(conn->bits.httpproxy)
      hostname = conn->http_proxy.host.name;
    else if(conn->bits.conn_to_host)
      hostname = conn->conn_to_host.name;
    else
      hostname = conn->host.name;

    failf(data, "Failed to connect to %s port %ld: %s",
          hostname, conn->port,
          Curl_strerror(error, buffer, sizeof(buffer)));
  }

  return result;
}