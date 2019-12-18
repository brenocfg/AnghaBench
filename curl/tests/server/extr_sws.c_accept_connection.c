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
typedef  int /*<<< orphan*/  flag ;
typedef  scalar_t__ curl_socket_t ;

/* Variables and functions */
 scalar_t__ CURL_SOCKET_BAD ; 
 int EAGAIN ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 size_t MAX_SOCKETS ; 
 int /*<<< orphan*/  SERVERLOGS_LOCK ; 
 int SOCKERRNO ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ accept (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__* all_sockets ; 
 scalar_t__ curlx_nonblock (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ got_exit_signal ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 size_t num_sockets ; 
 int /*<<< orphan*/  sclose (scalar_t__) ; 
 scalar_t__ serverlogslocked ; 
 int /*<<< orphan*/  set_advisor_read_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ socket_domain_is_ip () ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static curl_socket_t accept_connection(curl_socket_t sock)
{
  curl_socket_t msgsock = CURL_SOCKET_BAD;
  int error;
  int flag = 1;

  if(MAX_SOCKETS == num_sockets) {
    logmsg("Too many open sockets!");
    return CURL_SOCKET_BAD;
  }

  msgsock = accept(sock, NULL, NULL);

  if(got_exit_signal) {
    if(CURL_SOCKET_BAD != msgsock)
      sclose(msgsock);
    return CURL_SOCKET_BAD;
  }

  if(CURL_SOCKET_BAD == msgsock) {
    error = SOCKERRNO;
    if(EAGAIN == error || EWOULDBLOCK == error) {
      /* nothing to accept */
      return 0;
    }
    logmsg("MAJOR ERROR: accept() failed with error: (%d) %s",
           error, strerror(error));
    return CURL_SOCKET_BAD;
  }

  if(0 != curlx_nonblock(msgsock, TRUE)) {
    error = SOCKERRNO;
    logmsg("curlx_nonblock failed with error: (%d) %s",
           error, strerror(error));
    sclose(msgsock);
    return CURL_SOCKET_BAD;
  }

  if(0 != setsockopt(msgsock, SOL_SOCKET, SO_KEEPALIVE,
                     (void *)&flag, sizeof(flag))) {
    error = SOCKERRNO;
    logmsg("setsockopt(SO_KEEPALIVE) failed with error: (%d) %s",
           error, strerror(error));
    sclose(msgsock);
    return CURL_SOCKET_BAD;
  }

  /*
  ** As soon as this server accepts a connection from the test harness it
  ** must set the server logs advisor read lock to indicate that server
  ** logs should not be read until this lock is removed by this server.
  */

  if(!serverlogslocked)
    set_advisor_read_lock(SERVERLOGS_LOCK);
  serverlogslocked += 1;

  logmsg("====> Client connect");

  all_sockets[num_sockets] = msgsock;
  num_sockets += 1;

#ifdef TCP_NODELAY
  if(socket_domain_is_ip()) {
    /*
     * Disable the Nagle algorithm to make it easier to send out a large
     * response in many small segments to torture the clients more.
     */
    if(0 != setsockopt(msgsock, IPPROTO_TCP, TCP_NODELAY,
                       (void *)&flag, sizeof(flag)))
      logmsg("====> TCP_NODELAY failed");
  }
#endif

  return msgsock;
}