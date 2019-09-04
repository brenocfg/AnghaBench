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
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcp_fastopen; int /*<<< orphan*/  reuse; } ;
struct connectdata {scalar_t__ socktype; int /*<<< orphan*/  local_port; int /*<<< orphan*/  local_ip; int /*<<< orphan*/  primary_ip; int /*<<< orphan*/  ip_addr_str; int /*<<< orphan*/  primary_port; TYPE_1__ bits; struct Curl_easy* data; } ;
struct Curl_sockaddr_storage {int dummy; } ;
struct Curl_easy {int dummy; } ;
typedef  int /*<<< orphan*/  ssloc ;
typedef  int curl_socklen_t ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_persistconninfo (struct connectdata*) ; 
 int /*<<< orphan*/  Curl_strerror (int,char*,int) ; 
 int /*<<< orphan*/  MAX_IPADR_LEN ; 
 int SOCKERRNO ; 
 scalar_t__ SOCK_DGRAM ; 
 int STRERROR_LEN ; 
 int errno ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getaddressinfo (struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ getpeername (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct Curl_sockaddr_storage*,int /*<<< orphan*/ ,int) ; 

void Curl_updateconninfo(struct connectdata *conn, curl_socket_t sockfd)
{
  curl_socklen_t len;
  struct Curl_sockaddr_storage ssrem;
  struct Curl_sockaddr_storage ssloc;
  struct Curl_easy *data = conn->data;

  if(conn->socktype == SOCK_DGRAM)
    /* there's no connection! */
    return;

  if(!conn->bits.reuse && !conn->bits.tcp_fastopen) {
    char buffer[STRERROR_LEN];
    len = sizeof(struct Curl_sockaddr_storage);
    if(getpeername(sockfd, (struct sockaddr*) &ssrem, &len)) {
      int error = SOCKERRNO;
      failf(data, "getpeername() failed with errno %d: %s",
            error, Curl_strerror(error, buffer, sizeof(buffer)));
      return;
    }

    len = sizeof(struct Curl_sockaddr_storage);
    memset(&ssloc, 0, sizeof(ssloc));
    if(getsockname(sockfd, (struct sockaddr*) &ssloc, &len)) {
      int error = SOCKERRNO;
      failf(data, "getsockname() failed with errno %d: %s",
            error, Curl_strerror(error, buffer, sizeof(buffer)));
      return;
    }

    if(!getaddressinfo((struct sockaddr*)&ssrem,
                       conn->primary_ip, &conn->primary_port)) {
      failf(data, "ssrem inet_ntop() failed with errno %d: %s",
            errno, Curl_strerror(errno, buffer, sizeof(buffer)));
      return;
    }
    memcpy(conn->ip_addr_str, conn->primary_ip, MAX_IPADR_LEN);

    if(!getaddressinfo((struct sockaddr*)&ssloc,
                       conn->local_ip, &conn->local_port)) {
      failf(data, "ssloc inet_ntop() failed with errno %d: %s",
            errno, Curl_strerror(errno, buffer, sizeof(buffer)));
      return;
    }

  }

  /* persist connection info in session handle */
  Curl_persistconninfo(conn);
}