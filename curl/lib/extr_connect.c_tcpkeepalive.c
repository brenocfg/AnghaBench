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
typedef  int /*<<< orphan*/  vals ;
struct tcp_keepalive {int onoff; int keepalivetime; int keepaliveinterval; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcp_keepidle; int /*<<< orphan*/  tcp_keepintvl; scalar_t__ tcp_keepalive; } ;
struct Curl_easy {TYPE_1__ set; } ;
typedef  int /*<<< orphan*/  optval ;
typedef  scalar_t__ curl_socket_t ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  KEEPALIVE_FACTOR (int) ; 
 int /*<<< orphan*/  SIO_KEEPALIVE_VALS ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  TCP_KEEPALIVE ; 
 int /*<<< orphan*/  TCP_KEEPIDLE ; 
 int /*<<< orphan*/  TCP_KEEPINTVL ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ WSAIoctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int curlx_sltosi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,int,...) ; 
 scalar_t__ setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void
tcpkeepalive(struct Curl_easy *data,
             curl_socket_t sockfd)
{
  int optval = data->set.tcp_keepalive?1:0;

  /* only set IDLE and INTVL if setting KEEPALIVE is successful */
  if(setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE,
        (void *)&optval, sizeof(optval)) < 0) {
    infof(data, "Failed to set SO_KEEPALIVE on fd %d\n", sockfd);
  }
  else {
#if defined(SIO_KEEPALIVE_VALS)
    struct tcp_keepalive vals;
    DWORD dummy;
    vals.onoff = 1;
    optval = curlx_sltosi(data->set.tcp_keepidle);
    KEEPALIVE_FACTOR(optval);
    vals.keepalivetime = optval;
    optval = curlx_sltosi(data->set.tcp_keepintvl);
    KEEPALIVE_FACTOR(optval);
    vals.keepaliveinterval = optval;
    if(WSAIoctl(sockfd, SIO_KEEPALIVE_VALS, (LPVOID) &vals, sizeof(vals),
                NULL, 0, &dummy, NULL, NULL) != 0) {
      infof(data, "Failed to set SIO_KEEPALIVE_VALS on fd %d: %d\n",
            (int)sockfd, WSAGetLastError());
    }
#else
#ifdef TCP_KEEPIDLE
    optval = curlx_sltosi(data->set.tcp_keepidle);
    KEEPALIVE_FACTOR(optval);
    if(setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPIDLE,
          (void *)&optval, sizeof(optval)) < 0) {
      infof(data, "Failed to set TCP_KEEPIDLE on fd %d\n", sockfd);
    }
#endif
#ifdef TCP_KEEPINTVL
    optval = curlx_sltosi(data->set.tcp_keepintvl);
    KEEPALIVE_FACTOR(optval);
    if(setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPINTVL,
          (void *)&optval, sizeof(optval)) < 0) {
      infof(data, "Failed to set TCP_KEEPINTVL on fd %d\n", sockfd);
    }
#endif
#ifdef TCP_KEEPALIVE
    /* Mac OS X style */
    optval = curlx_sltosi(data->set.tcp_keepidle);
    KEEPALIVE_FACTOR(optval);
    if(setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPALIVE,
          (void *)&optval, sizeof(optval)) < 0) {
      infof(data, "Failed to set TCP_KEEPALIVE on fd %d\n", sockfd);
    }
#endif
#endif
  }
}