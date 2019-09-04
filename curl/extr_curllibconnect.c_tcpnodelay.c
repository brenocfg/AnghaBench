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
struct connectdata {int dummy; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;

/* Variables and functions */

__attribute__((used)) static void tcpnodelay(struct connectdata *conn, curl_socket_t sockfd)
{
#if defined(TCP_NODELAY)
#if !defined(CURL_DISABLE_VERBOSE_STRINGS)
  struct Curl_easy *data = conn->data;
#endif
  curl_socklen_t onoff = (curl_socklen_t) 1;
  int level = IPPROTO_TCP;
  char buffer[STRERROR_LEN];

#if defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void) conn;
#endif

  if(setsockopt(sockfd, level, TCP_NODELAY, (void *)&onoff,
                sizeof(onoff)) < 0)
    infof(data, "Could not set TCP_NODELAY: %s\n",
          Curl_strerror(SOCKERRNO, buffer, sizeof(buffer)));
  else
    infof(data, "TCP_NODELAY set\n");
#else
  (void)conn;
  (void)sockfd;
#endif
}