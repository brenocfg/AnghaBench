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
struct perclient {int used; scalar_t__ clientfd; scalar_t__ remotefd; scalar_t__ fromremote; scalar_t__ fromclient; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  scalar_t__ curl_socket_t ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 scalar_t__ CURL_SOCKET_BAD ; 
 int EINTR ; 
 int FALSE ; 
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int SOCKERRNO ; 
 int TRUE ; 
 scalar_t__ accept (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ configfile ; 
 int errno ; 
 int getppid () ; 
 scalar_t__ got_exit_signal ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 int /*<<< orphan*/  memset (struct perclient*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sclose (scalar_t__) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sockit (scalar_t__) ; 
 scalar_t__ strerror (int) ; 
 scalar_t__ tunnel (struct perclient*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool incoming(curl_socket_t listenfd)
{
  fd_set fds_read;
  fd_set fds_write;
  fd_set fds_err;
  int clients = 0; /* connected clients */
  struct perclient c[2];

  memset(c, 0, sizeof(c));
  if(got_exit_signal) {
    logmsg("signalled to die, exiting...");
    return FALSE;
  }

#ifdef HAVE_GETPPID
  /* As a last resort, quit if socks5 process becomes orphan. */
  if(getppid() <= 1) {
    logmsg("process becomes orphan, exiting");
    return FALSE;
  }
#endif

  do {
    int i;
    ssize_t rc;
    int error = 0;
    curl_socket_t sockfd = listenfd;
    int maxfd = (int)sockfd;

    FD_ZERO(&fds_read);
    FD_ZERO(&fds_write);
    FD_ZERO(&fds_err);

    /* there's always a socket to wait for */
    FD_SET(sockfd, &fds_read);

    for(i = 0; i < 2; i++) {
      if(c[i].used) {
        curl_socket_t fd = c[i].clientfd;
        FD_SET(fd, &fds_read);
        if((int)fd > maxfd)
          maxfd = (int)fd;
        fd = c[i].remotefd;
        FD_SET(fd, &fds_read);
        if((int)fd > maxfd)
          maxfd = (int)fd;
      }
    }

    do {
      /* select() blocking behavior call on blocking descriptors please */
      rc = select(maxfd + 1, &fds_read, &fds_write, &fds_err, NULL);
      if(got_exit_signal) {
        logmsg("signalled to die, exiting...");
        return FALSE;
      }
    } while((rc == -1) && ((error = errno) == EINTR));

    if(rc < 0) {
      logmsg("select() failed with error: (%d) %s",
             error, strerror(error));
      return FALSE;
    }

    if((clients < 2) && FD_ISSET(sockfd, &fds_read)) {
      curl_socket_t newfd = accept(sockfd, NULL, NULL);
      if(CURL_SOCKET_BAD == newfd) {
        error = SOCKERRNO;
        logmsg("accept(%d, NULL, NULL) failed with error: (%d) %s",
               sockfd, error, strerror(error));
      }
      else {
        curl_socket_t remotefd;
        logmsg("====> Client connect, fd %d. Read config from %s",
               newfd, configfile);
        remotefd = sockit(newfd); /* SOCKS until done */
        if(remotefd == CURL_SOCKET_BAD) {
          logmsg("====> Client disconnect");
          sclose(newfd);
        }
        else {
          struct perclient *cp = &c[0];
          logmsg("====> Tunnel transfer");

          if(c[0].used)
            cp = &c[1];
          cp->fromremote = 0;
          cp->fromclient = 0;
          cp->clientfd = newfd;
          cp->remotefd = remotefd;
          cp->used = TRUE;
          clients++;
        }

      }
    }
    for(i = 0; i < 2; i++) {
      struct perclient *cp = &c[i];
      if(cp->used) {
        if(tunnel(cp, &fds_read)) {
          logmsg("SOCKS transfer completed. Bytes: < %zu > %zu",
                 cp->fromremote, cp->fromclient);
          sclose(cp->clientfd);
          sclose(cp->remotefd);
          cp->used = FALSE;
          clients--;
        }
      }
    }
  } while(clients);

  return TRUE;
}