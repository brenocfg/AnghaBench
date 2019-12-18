#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct httprequest {scalar_t__ testno; int partno; scalar_t__ open; void* pipelining; void* sin6_port; int /*<<< orphan*/  sin6_addr; void* sin6_family; void* sin_port; TYPE_1__ sin_addr; void* sin_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  sa; struct httprequest sa6; struct httprequest sa4; } ;
typedef  TYPE_2__ srvr_sockaddr_union_t ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  flag ;
typedef  scalar_t__ curl_socket_t ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
 scalar_t__ CURL_SOCKET_BAD ; 
 unsigned short DEFAULT_PORT ; 
 scalar_t__ DOCNUMBER_CONNECT ; 
 scalar_t__ DOCNUMBER_QUIT ; 
 void* FALSE ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SERVERLOGS_LOCK ; 
 int SOCKERRNO ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 void* TRUE ; 
 scalar_t__ accept (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int bind (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clear_advisor_read_lock (int /*<<< orphan*/ ) ; 
 unsigned short curlx_ultous (unsigned long) ; 
 int /*<<< orphan*/  exit_signal ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ get_request (scalar_t__,struct httprequest*) ; 
 scalar_t__ getpid () ; 
 scalar_t__ got_exit_signal ; 
 void* htons (unsigned short) ; 
 int /*<<< orphan*/  in6addr_any ; 
 int /*<<< orphan*/  install_signal_handlers () ; 
 char* ipv_inuse ; 
 int listen (scalar_t__,int) ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 int /*<<< orphan*/  memset (struct httprequest*,int /*<<< orphan*/ ,int) ; 
 char* path ; 
 void* prevbounce ; 
 int prevpartno ; 
 int prevtestno ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_signal_handlers () ; 
 int /*<<< orphan*/  sclose (scalar_t__) ; 
 int /*<<< orphan*/  send_doc (scalar_t__,struct httprequest*) ; 
 char* serverlogfile ; 
 int serverlogslocked ; 
 int /*<<< orphan*/  set_advisor_read_lock (int /*<<< orphan*/ ) ; 
 int setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ socket (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int strlen (char*) ; 
 unsigned long strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 void* use_ipv6 ; 
 int /*<<< orphan*/  win32_cleanup ; 
 int /*<<< orphan*/  win32_init () ; 
 int write_pidfile (char const*) ; 

int main(int argc, char *argv[])
{
  srvr_sockaddr_union_t me;
  curl_socket_t sock = CURL_SOCKET_BAD;
  curl_socket_t msgsock = CURL_SOCKET_BAD;
  int wrotepidfile = 0;
  int flag;
  unsigned short port = DEFAULT_PORT;
  const char *pidname = ".rtsp.pid";
  struct httprequest req;
  int rc;
  int error;
  int arg = 1;
  long pid;

  memset(&req, 0, sizeof(req));

  while(argc>arg) {
    if(!strcmp("--version", argv[arg])) {
      printf("rtspd IPv4%s"
             "\n"
             ,
#ifdef ENABLE_IPV6
             "/IPv6"
#else
             ""
#endif
             );
      return 0;
    }
    else if(!strcmp("--pidfile", argv[arg])) {
      arg++;
      if(argc>arg)
        pidname = argv[arg++];
    }
    else if(!strcmp("--logfile", argv[arg])) {
      arg++;
      if(argc>arg)
        serverlogfile = argv[arg++];
    }
    else if(!strcmp("--ipv4", argv[arg])) {
#ifdef ENABLE_IPV6
      ipv_inuse = "IPv4";
      use_ipv6 = FALSE;
#endif
      arg++;
    }
    else if(!strcmp("--ipv6", argv[arg])) {
#ifdef ENABLE_IPV6
      ipv_inuse = "IPv6";
      use_ipv6 = TRUE;
#endif
      arg++;
    }
    else if(!strcmp("--port", argv[arg])) {
      arg++;
      if(argc>arg) {
        char *endptr;
        unsigned long ulnum = strtoul(argv[arg], &endptr, 10);
        if((endptr != argv[arg] + strlen(argv[arg])) ||
           (ulnum < 1025UL) || (ulnum > 65535UL)) {
          fprintf(stderr, "rtspd: invalid --port argument (%s)\n",
                  argv[arg]);
          return 0;
        }
        port = curlx_ultous(ulnum);
        arg++;
      }
    }
    else if(!strcmp("--srcdir", argv[arg])) {
      arg++;
      if(argc>arg) {
        path = argv[arg];
        arg++;
      }
    }
    else {
      puts("Usage: rtspd [option]\n"
           " --version\n"
           " --logfile [file]\n"
           " --pidfile [file]\n"
           " --ipv4\n"
           " --ipv6\n"
           " --port [port]\n"
           " --srcdir [path]");
      return 0;
    }
  }

#ifdef WIN32
  win32_init();
  atexit(win32_cleanup);
#endif

  install_signal_handlers();

  pid = (long)getpid();

#ifdef ENABLE_IPV6
  if(!use_ipv6)
#endif
    sock = socket(AF_INET, SOCK_STREAM, 0);
#ifdef ENABLE_IPV6
  else
    sock = socket(AF_INET6, SOCK_STREAM, 0);
#endif

  if(CURL_SOCKET_BAD == sock) {
    error = SOCKERRNO;
    logmsg("Error creating socket: (%d) %s",
           error, strerror(error));
    goto server_cleanup;
  }

  flag = 1;
  if(0 != setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
            (void *)&flag, sizeof(flag))) {
    error = SOCKERRNO;
    logmsg("setsockopt(SO_REUSEADDR) failed with error: (%d) %s",
           error, strerror(error));
    goto server_cleanup;
  }

#ifdef ENABLE_IPV6
  if(!use_ipv6) {
#endif
    memset(&me.sa4, 0, sizeof(me.sa4));
    me.sa4.sin_family = AF_INET;
    me.sa4.sin_addr.s_addr = INADDR_ANY;
    me.sa4.sin_port = htons(port);
    rc = bind(sock, &me.sa, sizeof(me.sa4));
#ifdef ENABLE_IPV6
  }
  else {
    memset(&me.sa6, 0, sizeof(me.sa6));
    me.sa6.sin6_family = AF_INET6;
    me.sa6.sin6_addr = in6addr_any;
    me.sa6.sin6_port = htons(port);
    rc = bind(sock, &me.sa, sizeof(me.sa6));
  }
#endif /* ENABLE_IPV6 */
  if(0 != rc) {
    error = SOCKERRNO;
    logmsg("Error binding socket on port %hu: (%d) %s",
           port, error, strerror(error));
    goto server_cleanup;
  }

  logmsg("Running %s version on port %d", ipv_inuse, (int)port);

  /* start accepting connections */
  rc = listen(sock, 5);
  if(0 != rc) {
    error = SOCKERRNO;
    logmsg("listen() failed with error: (%d) %s",
           error, strerror(error));
    goto server_cleanup;
  }

  /*
  ** As soon as this server writes its pid file the test harness will
  ** attempt to connect to this server and initiate its verification.
  */

  wrotepidfile = write_pidfile(pidname);
  if(!wrotepidfile)
    goto server_cleanup;

  for(;;) {
    msgsock = accept(sock, NULL, NULL);

    if(got_exit_signal)
      break;
    if(CURL_SOCKET_BAD == msgsock) {
      error = SOCKERRNO;
      logmsg("MAJOR ERROR: accept() failed with error: (%d) %s",
             error, strerror(error));
      break;
    }

    /*
    ** As soon as this server acepts a connection from the test harness it
    ** must set the server logs advisor read lock to indicate that server
    ** logs should not be read until this lock is removed by this server.
    */

    set_advisor_read_lock(SERVERLOGS_LOCK);
    serverlogslocked = 1;

    logmsg("====> Client connect");

#ifdef TCP_NODELAY
    /*
     * Disable the Nagle algorithm to make it easier to send out a large
     * response in many small segments to torture the clients more.
     */
    flag = 1;
    if(setsockopt(msgsock, IPPROTO_TCP, TCP_NODELAY,
                   (void *)&flag, sizeof(flag)) == -1) {
      logmsg("====> TCP_NODELAY failed");
    }
#endif

    /* initialization of httprequest struct is done in get_request(), but due
       to pipelining treatment the pipelining struct field must be initialized
       previously to FALSE every time a new connection arrives. */

    req.pipelining = FALSE;

    do {
      if(got_exit_signal)
        break;

      if(get_request(msgsock, &req))
        /* non-zero means error, break out of loop */
        break;

      if(prevbounce) {
        /* bounce treatment requested */
        if((req.testno == prevtestno) &&
           (req.partno == prevpartno)) {
          req.partno++;
          logmsg("BOUNCE part number to %ld", req.partno);
        }
        else {
          prevbounce = FALSE;
          prevtestno = -1;
          prevpartno = -1;
        }
      }

      send_doc(msgsock, &req);
      if(got_exit_signal)
        break;

      if((req.testno < 0) && (req.testno != DOCNUMBER_CONNECT)) {
        logmsg("special request received, no persistency");
        break;
      }
      if(!req.open) {
        logmsg("instructed to close connection after server-reply");
        break;
      }

      if(req.open)
        logmsg("=> persistent connection request ended, awaits new request");
      /* if we got a CONNECT, loop and get another request as well! */
    } while(req.open || (req.testno == DOCNUMBER_CONNECT));

    if(got_exit_signal)
      break;

    logmsg("====> Client disconnect");
    sclose(msgsock);
    msgsock = CURL_SOCKET_BAD;

    if(serverlogslocked) {
      serverlogslocked = 0;
      clear_advisor_read_lock(SERVERLOGS_LOCK);
    }

    if(req.testno == DOCNUMBER_QUIT)
      break;
  }

server_cleanup:

  if((msgsock != sock) && (msgsock != CURL_SOCKET_BAD))
    sclose(msgsock);

  if(sock != CURL_SOCKET_BAD)
    sclose(sock);

  if(got_exit_signal)
    logmsg("signalled to die");

  if(wrotepidfile)
    unlink(pidname);

  if(serverlogslocked) {
    serverlogslocked = 0;
    clear_advisor_read_lock(SERVERLOGS_LOCK);
  }

  restore_signal_handlers();

  if(got_exit_signal) {
    logmsg("========> %s rtspd (port: %d pid: %ld) exits with signal (%d)",
           ipv_inuse, (int)port, pid, exit_signal);
    /*
     * To properly set the return status of the process we
     * must raise the same signal SIGINT or SIGTERM that we
     * caught and let the old handler take care of it.
     */
    raise(exit_signal);
  }

  logmsg("========> rtspd quits");
  return 0;
}