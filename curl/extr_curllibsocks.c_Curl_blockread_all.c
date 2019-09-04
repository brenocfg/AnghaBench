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
typedef  scalar_t__ timediff_t ;
struct connectdata {int /*<<< orphan*/  data; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  curl_socket_t ;

/* Variables and functions */
 int CURLE_AGAIN ; 
 int CURLE_OK ; 
 int CURLE_OPERATION_TIMEDOUT ; 
 int Curl_read_plain (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__*) ; 
 scalar_t__ Curl_timeleft (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SOCKET_READABLE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

int Curl_blockread_all(struct connectdata *conn, /* connection data */
                       curl_socket_t sockfd,     /* read from this socket */
                       char *buf,                /* store read data here */
                       ssize_t buffersize,       /* max amount to read */
                       ssize_t *n)               /* amount bytes read */
{
  ssize_t nread = 0;
  ssize_t allread = 0;
  int result;
  *n = 0;
  for(;;) {
    timediff_t timeleft = Curl_timeleft(conn->data, NULL, TRUE);
    if(timeleft < 0) {
      /* we already got the timeout */
      result = CURLE_OPERATION_TIMEDOUT;
      break;
    }
    if(SOCKET_READABLE(sockfd, timeleft) <= 0) {
      result = ~CURLE_OK;
      break;
    }
    result = Curl_read_plain(sockfd, buf, buffersize, &nread);
    if(CURLE_AGAIN == result)
      continue;
    if(result)
      break;

    if(buffersize == nread) {
      allread += nread;
      *n = allread;
      result = CURLE_OK;
      break;
    }
    if(!nread) {
      result = ~CURLE_OK;
      break;
    }

    buffersize -= nread;
    buf += nread;
    allread += nread;
  }
  return result;
}