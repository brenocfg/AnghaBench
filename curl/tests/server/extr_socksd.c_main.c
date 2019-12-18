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
typedef  scalar_t__ curl_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  O_BINARY ; 
 int SOCKERRNO ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 scalar_t__ atoi (char*) ; 
 char* backendaddr ; 
 unsigned short backendport ; 
 char* configfile ; 
 int /*<<< orphan*/  curlx_ultous (unsigned long) ; 
 int /*<<< orphan*/  exit_signal ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ got_exit_signal ; 
 int incoming (scalar_t__) ; 
 int /*<<< orphan*/  install_signal_handlers () ; 
 char* ipv_inuse ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_signal_handlers () ; 
 int /*<<< orphan*/  sclose (scalar_t__) ; 
 char* serverlogfile ; 
 int /*<<< orphan*/  setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sockdaemon (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int strlen (char*) ; 
 unsigned long strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 int /*<<< orphan*/  use_ipv6 ; 
 int /*<<< orphan*/  win32_cleanup ; 
 int /*<<< orphan*/  win32_init () ; 
 int write_pidfile (char const*) ; 

int main(int argc, char *argv[])
{
  curl_socket_t sock = CURL_SOCKET_BAD;
  curl_socket_t msgsock = CURL_SOCKET_BAD;
  int wrotepidfile = 0;
  const char *pidname = ".socksd.pid";
  bool juggle_again;
  int error;
  int arg = 1;

  while(argc>arg) {
    if(!strcmp("--version", argv[arg])) {
      printf("socksd IPv4%s\n",
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
    else if(!strcmp("--config", argv[arg])) {
      arg++;
      if(argc>arg)
        configfile = argv[arg++];
    }
    else if(!strcmp("--backend", argv[arg])) {
      arg++;
      if(argc>arg)
        backendaddr = argv[arg++];
    }
    else if(!strcmp("--backendport", argv[arg])) {
      arg++;
      if(argc>arg)
        backendport = (unsigned short)atoi(argv[arg++]);
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
    else if(!strcmp("--port", argv[arg])) {
      arg++;
      if(argc>arg) {
        char *endptr;
        unsigned long ulnum = strtoul(argv[arg], &endptr, 10);
        if((endptr != argv[arg] + strlen(argv[arg])) ||
           ((ulnum != 0UL) && ((ulnum < 1025UL) || (ulnum > 65535UL)))) {
          fprintf(stderr, "socksd: invalid --port argument (%s)\n",
                  argv[arg]);
          return 0;
        }
        port = curlx_ultous(ulnum);
        arg++;
      }
    }
    else {
      puts("Usage: socksd [option]\n"
           " --backend [ipv4 addr]\n"
           " --backendport [TCP port]\n"
           " --config [file]\n"
           " --version\n"
           " --logfile [file]\n"
           " --pidfile [file]\n"
           " --ipv4\n"
           " --ipv6\n"
           " --bindonly\n"
           " --port [port]\n");
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
    goto socks5_cleanup;
  }

  {
    /* passive daemon style */
    sock = sockdaemon(sock, &port);
    if(CURL_SOCKET_BAD == sock) {
      goto socks5_cleanup;
    }
    msgsock = CURL_SOCKET_BAD; /* no stream socket yet */
  }

  logmsg("Running %s version", ipv_inuse);
  logmsg("Listening on port %hu", port);

  wrotepidfile = write_pidfile(pidname);
  if(!wrotepidfile) {
    goto socks5_cleanup;
  }

  do {
    juggle_again = incoming(sock);
  } while(juggle_again);

socks5_cleanup:

  if((msgsock != sock) && (msgsock != CURL_SOCKET_BAD))
    sclose(msgsock);

  if(sock != CURL_SOCKET_BAD)
    sclose(sock);

  if(wrotepidfile)
    unlink(pidname);

  restore_signal_handlers();

  if(got_exit_signal) {
    logmsg("============> socksd exits with signal (%d)", exit_signal);
    /*
     * To properly set the return status of the process we
     * must raise the same signal SIGINT or SIGTERM that we
     * caught and let the old handler take care of it.
     */
    raise(exit_signal);
  }

  logmsg("============> socksd quits");
  return 0;
}