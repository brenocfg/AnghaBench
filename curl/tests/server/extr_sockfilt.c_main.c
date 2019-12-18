#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_5__ {TYPE_3__ sin6_addr; void* sin6_port; void* sin6_family; TYPE_3__ sin_addr; void* sin_port; void* sin_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  sa; TYPE_2__ sa6; TYPE_2__ sa4; } ;
typedef  TYPE_1__ srvr_sockaddr_union_t ;
typedef  enum sockmode { ____Placeholder_sockmode } sockmode ;
typedef  scalar_t__ curl_socket_t ;

/* Variables and functions */
 int ACTIVE ; 
 void* AF_INET ; 
 void* AF_INET6 ; 
 scalar_t__ CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  Curl_inet_pton (void*,char const*,TYPE_3__*) ; 
 void* FALSE ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  O_BINARY ; 
 int PASSIVE_LISTEN ; 
 int SOCKERRNO ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 void* TRUE ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 void* bind_only ; 
 int connect (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int connectport ; 
 void* curlx_ultous (unsigned long) ; 
 int /*<<< orphan*/  exit_signal ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ got_exit_signal ; 
 void* htons (int) ; 
 int /*<<< orphan*/  install_signal_handlers () ; 
 char* ipv_inuse ; 
 int juggle (scalar_t__*,scalar_t__,int*) ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 void* port ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_signal_handlers () ; 
 int /*<<< orphan*/  sclose (scalar_t__) ; 
 char* serverlogfile ; 
 int /*<<< orphan*/  setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sockdaemon (scalar_t__,void**) ; 
 scalar_t__ socket (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int strlen (char*) ; 
 unsigned long strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 void* use_ipv6 ; 
 void* verbose ; 
 int /*<<< orphan*/  win32_cleanup ; 
 int /*<<< orphan*/  win32_init () ; 
 int write_pidfile (char const*) ; 
 int /*<<< orphan*/  write_stdout (char*,int) ; 

int main(int argc, char *argv[])
{
  srvr_sockaddr_union_t me;
  curl_socket_t sock = CURL_SOCKET_BAD;
  curl_socket_t msgsock = CURL_SOCKET_BAD;
  int wrotepidfile = 0;
  const char *pidname = ".sockfilt.pid";
  bool juggle_again;
  int rc;
  int error;
  int arg = 1;
  enum sockmode mode = PASSIVE_LISTEN; /* default */
  const char *addr = NULL;

  while(argc>arg) {
    if(!strcmp("--version", argv[arg])) {
      printf("sockfilt IPv4%s\n",
#ifdef ENABLE_IPV6
             "/IPv6"
#else
             ""
#endif
             );
      return 0;
    }
    else if(!strcmp("--verbose", argv[arg])) {
      verbose = TRUE;
      arg++;
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
    else if(!strcmp("--ipv6", argv[arg])) {
#ifdef ENABLE_IPV6
      ipv_inuse = "IPv6";
      use_ipv6 = TRUE;
#endif
      arg++;
    }
    else if(!strcmp("--ipv4", argv[arg])) {
      /* for completeness, we support this option as well */
#ifdef ENABLE_IPV6
      ipv_inuse = "IPv4";
      use_ipv6 = FALSE;
#endif
      arg++;
    }
    else if(!strcmp("--bindonly", argv[arg])) {
      bind_only = TRUE;
      arg++;
    }
    else if(!strcmp("--port", argv[arg])) {
      arg++;
      if(argc>arg) {
        char *endptr;
        unsigned long ulnum = strtoul(argv[arg], &endptr, 10);
        if((endptr != argv[arg] + strlen(argv[arg])) ||
           ((ulnum != 0UL) && ((ulnum < 1025UL) || (ulnum > 65535UL)))) {
          fprintf(stderr, "sockfilt: invalid --port argument (%s)\n",
                  argv[arg]);
          return 0;
        }
        port = curlx_ultous(ulnum);
        arg++;
      }
    }
    else if(!strcmp("--connect", argv[arg])) {
      /* Asked to actively connect to the specified local port instead of
         doing a passive server-style listening. */
      arg++;
      if(argc>arg) {
        char *endptr;
        unsigned long ulnum = strtoul(argv[arg], &endptr, 10);
        if((endptr != argv[arg] + strlen(argv[arg])) ||
           (ulnum < 1025UL) || (ulnum > 65535UL)) {
          fprintf(stderr, "sockfilt: invalid --connect argument (%s)\n",
                  argv[arg]);
          return 0;
        }
        connectport = curlx_ultous(ulnum);
        arg++;
      }
    }
    else if(!strcmp("--addr", argv[arg])) {
      /* Set an IP address to use with --connect; otherwise use localhost */
      arg++;
      if(argc>arg) {
        addr = argv[arg];
        arg++;
      }
    }
    else {
      puts("Usage: sockfilt [option]\n"
           " --version\n"
           " --verbose\n"
           " --logfile [file]\n"
           " --pidfile [file]\n"
           " --ipv4\n"
           " --ipv6\n"
           " --bindonly\n"
           " --port [port]\n"
           " --connect [port]\n"
           " --addr [address]");
      return 0;
    }
  }

#ifdef WIN32
  win32_init();
  atexit(win32_cleanup);

  setmode(fileno(stdin), O_BINARY);
  setmode(fileno(stdout), O_BINARY);
  setmode(fileno(stderr), O_BINARY);
#endif

  install_signal_handlers();

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
    write_stdout("FAIL\n", 5);
    goto sockfilt_cleanup;
  }

  if(connectport) {
    /* Active mode, we should connect to the given port number */
    mode = ACTIVE;
#ifdef ENABLE_IPV6
    if(!use_ipv6) {
#endif
      memset(&me.sa4, 0, sizeof(me.sa4));
      me.sa4.sin_family = AF_INET;
      me.sa4.sin_port = htons(connectport);
      me.sa4.sin_addr.s_addr = INADDR_ANY;
      if(!addr)
        addr = "127.0.0.1";
      Curl_inet_pton(AF_INET, addr, &me.sa4.sin_addr);

      rc = connect(sock, &me.sa, sizeof(me.sa4));
#ifdef ENABLE_IPV6
    }
    else {
      memset(&me.sa6, 0, sizeof(me.sa6));
      me.sa6.sin6_family = AF_INET6;
      me.sa6.sin6_port = htons(connectport);
      if(!addr)
        addr = "::1";
      Curl_inet_pton(AF_INET6, addr, &me.sa6.sin6_addr);

      rc = connect(sock, &me.sa, sizeof(me.sa6));
    }
#endif /* ENABLE_IPV6 */
    if(rc) {
      error = SOCKERRNO;
      logmsg("Error connecting to port %hu: (%d) %s",
             connectport, error, strerror(error));
      write_stdout("FAIL\n", 5);
      goto sockfilt_cleanup;
    }
    logmsg("====> Client connect");
    msgsock = sock; /* use this as stream */
  }
  else {
    /* passive daemon style */
    sock = sockdaemon(sock, &port);
    if(CURL_SOCKET_BAD == sock) {
      write_stdout("FAIL\n", 5);
      goto sockfilt_cleanup;
    }
    msgsock = CURL_SOCKET_BAD; /* no stream socket yet */
  }

  logmsg("Running %s version", ipv_inuse);

  if(connectport)
    logmsg("Connected to port %hu", connectport);
  else if(bind_only)
    logmsg("Bound without listening on port %hu", port);
  else
    logmsg("Listening on port %hu", port);

  wrotepidfile = write_pidfile(pidname);
  if(!wrotepidfile) {
    write_stdout("FAIL\n", 5);
    goto sockfilt_cleanup;
  }

  do {
    juggle_again = juggle(&msgsock, sock, &mode);
  } while(juggle_again);

sockfilt_cleanup:

  if((msgsock != sock) && (msgsock != CURL_SOCKET_BAD))
    sclose(msgsock);

  if(sock != CURL_SOCKET_BAD)
    sclose(sock);

  if(wrotepidfile)
    unlink(pidname);

  restore_signal_handlers();

  if(got_exit_signal) {
    logmsg("============> sockfilt exits with signal (%d)", exit_signal);
    /*
     * To properly set the return status of the process we
     * must raise the same signal SIGINT or SIGTERM that we
     * caught and let the old handler take care of it.
     */
    raise(exit_signal);
  }

  logmsg("============> sockfilt quits");
  return 0;
}