#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct pingpong {int /*<<< orphan*/  pending_resp; scalar_t__ cache; } ;
struct ftp_conn {struct pingpong pp; } ;
struct TYPE_2__ {struct ftp_conn ftpc; } ;
struct connectdata {TYPE_1__ proto; struct Curl_easy* data; int /*<<< orphan*/ * sock; } ;
struct Curl_easy {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_ABORTED_BY_CALLBACK ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OPERATION_TIMEDOUT ; 
 scalar_t__ CURLE_RECV_ERROR ; 
 int /*<<< orphan*/  Curl_conn_data_pending (struct connectdata*,size_t) ; 
 int /*<<< orphan*/  Curl_pgrsUpdate (struct connectdata*) ; 
 int Curl_pp_state_timeout (struct pingpong*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 size_t FIRSTSOCKET ; 
 int /*<<< orphan*/  SOCKERRNO ; 
 int SOCKET_READABLE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,...) ; 
 scalar_t__ ftp_readresp (int /*<<< orphan*/ ,struct pingpong*,int*,size_t*) ; 

CURLcode Curl_GetFTPResponse(ssize_t *nreadp, /* return number of bytes read */
                             struct connectdata *conn,
                             int *ftpcode) /* return the ftp-code */
{
  /*
   * We cannot read just one byte per read() and then go back to select() as
   * the OpenSSL read() doesn't grok that properly.
   *
   * Alas, read as much as possible, split up into lines, use the ending
   * line in a response or continue reading.  */

  curl_socket_t sockfd = conn->sock[FIRSTSOCKET];
  struct Curl_easy *data = conn->data;
  CURLcode result = CURLE_OK;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  struct pingpong *pp = &ftpc->pp;
  size_t nread;
  int cache_skip = 0;
  int value_to_be_ignored = 0;

  if(ftpcode)
    *ftpcode = 0; /* 0 for errors */
  else
    /* make the pointer point to something for the rest of this function */
    ftpcode = &value_to_be_ignored;

  *nreadp = 0;

  while(!*ftpcode && !result) {
    /* check and reset timeout value every lap */
    time_t timeout = Curl_pp_state_timeout(pp, FALSE);
    time_t interval_ms;

    if(timeout <= 0) {
      failf(data, "FTP response timeout");
      return CURLE_OPERATION_TIMEDOUT; /* already too little time */
    }

    interval_ms = 1000;  /* use 1 second timeout intervals */
    if(timeout < interval_ms)
      interval_ms = timeout;

    /*
     * Since this function is blocking, we need to wait here for input on the
     * connection and only then we call the response reading function. We do
     * timeout at least every second to make the timeout check run.
     *
     * A caution here is that the ftp_readresp() function has a cache that may
     * contain pieces of a response from the previous invoke and we need to
     * make sure we don't just wait for input while there is unhandled data in
     * that cache. But also, if the cache is there, we call ftp_readresp() and
     * the cache wasn't good enough to continue we must not just busy-loop
     * around this function.
     *
     */

    if(pp->cache && (cache_skip < 2)) {
      /*
       * There's a cache left since before. We then skipping the wait for
       * socket action, unless this is the same cache like the previous round
       * as then the cache was deemed not enough to act on and we then need to
       * wait for more data anyway.
       */
    }
    else if(!Curl_conn_data_pending(conn, FIRSTSOCKET)) {
      switch(SOCKET_READABLE(sockfd, interval_ms)) {
      case -1: /* select() error, stop reading */
        failf(data, "FTP response aborted due to select/poll error: %d",
              SOCKERRNO);
        return CURLE_RECV_ERROR;

      case 0: /* timeout */
        if(Curl_pgrsUpdate(conn))
          return CURLE_ABORTED_BY_CALLBACK;
        continue; /* just continue in our loop for the timeout duration */

      default: /* for clarity */
        break;
      }
    }
    result = ftp_readresp(sockfd, pp, ftpcode, &nread);
    if(result)
      break;

    if(!nread && pp->cache)
      /* bump cache skip counter as on repeated skips we must wait for more
         data */
      cache_skip++;
    else
      /* when we got data or there is no cache left, we reset the cache skip
         counter */
      cache_skip = 0;

    *nreadp += nread;

  } /* while there's buffer left and loop is requested */

  pp->pending_resp = FALSE;

  return result;
}