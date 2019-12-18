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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_AGAIN ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_RECV_ERROR ; 
 int EAGAIN ; 
 int EINTR ; 
 int EWOULDBLOCK ; 
 int SOCKERRNO ; 
 int WSAEWOULDBLOCK ; 
 int sread (int /*<<< orphan*/ ,char*,size_t) ; 

CURLcode Curl_read_plain(curl_socket_t sockfd,
                         char *buf,
                         size_t bytesfromsocket,
                         ssize_t *n)
{
  ssize_t nread = sread(sockfd, buf, bytesfromsocket);

  if(-1 == nread) {
    int err = SOCKERRNO;
    int return_error;
#ifdef USE_WINSOCK
    return_error = WSAEWOULDBLOCK == err;
#else
    return_error = EWOULDBLOCK == err || EAGAIN == err || EINTR == err;
#endif
    if(return_error)
      return CURLE_AGAIN;
    return CURLE_RECV_ERROR;
  }

  /* we only return number of bytes read when we return OK */
  *n = nread;
  return CURLE_OK;
}