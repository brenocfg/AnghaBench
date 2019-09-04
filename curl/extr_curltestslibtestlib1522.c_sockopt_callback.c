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
typedef  int /*<<< orphan*/  curlsocktype ;
typedef  int /*<<< orphan*/  curl_socket_t ;

/* Variables and functions */
 int CURL_SOCKOPT_OK ; 

__attribute__((used)) static int sockopt_callback(void *clientp, curl_socket_t curlfd,
                            curlsocktype purpose)
{
#if defined(SOL_SOCKET) && defined(SO_SNDBUF)
  int sndbufsize = 4 * 1024; /* 4KB send buffer */
  (void) clientp;
  (void) purpose;
  setsockopt(curlfd, SOL_SOCKET, SO_SNDBUF,
             (const char *)&sndbufsize, sizeof(sndbufsize));
#else
  (void)clientp;
  (void)curlfd;
  (void)purpose;
#endif
  return CURL_SOCKOPT_OK;
}