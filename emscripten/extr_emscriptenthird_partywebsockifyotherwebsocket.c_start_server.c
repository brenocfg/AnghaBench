#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ws_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sopt ;
typedef  int /*<<< orphan*/  serv_addr ;
typedef  int /*<<< orphan*/  cli_addr ;
struct TYPE_4__ {int listen_port; char* listen_host; int handler_id; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ *) ;scalar_t__ run_once; scalar_t__ daemon; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int accept (int,struct sockaddr*,int*) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  daemonize (int) ; 
 int /*<<< orphan*/ * do_handshake (int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int fork () ; 
 int /*<<< orphan*/  free_ws_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handler_emsg (char*) ; 
 int /*<<< orphan*/  handler_msg (char*,...) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_2__) ; 
 int /*<<< orphan*/  listen (int,int) ; 
 scalar_t__ pipe_error ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int resolve_host (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__ settings ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ws_socket_free (int /*<<< orphan*/ *) ; 

void start_server() {
    int lsock, csock, pid, clilen, sopt = 1, i;
    struct sockaddr_in serv_addr, cli_addr;
    ws_ctx_t *ws_ctx;


    /* Initialize buffers */
    lsock = socket(AF_INET, SOCK_STREAM, 0);
    if (lsock < 0) { error("ERROR creating listener socket"); }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(settings.listen_port);

    /* Resolve listen address */
    if (settings.listen_host && (settings.listen_host[0] != '\0')) {
        if (resolve_host(&serv_addr.sin_addr, settings.listen_host) < -1) {
            fatal("Could not resolve listen address");
        }
    } else {
        serv_addr.sin_addr.s_addr = INADDR_ANY;
    }

    setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, (char *)&sopt, sizeof(sopt));
    if (bind(lsock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        fatal("ERROR on binding listener socket");
    }
    listen(lsock,100);

    signal(SIGPIPE, signal_handler);  // catch pipe

    if (settings.daemon) {
        daemonize(lsock);
    }


    // Reep zombies
    signal(SIGCHLD, SIG_IGN);

    printf("Waiting for connections on %s:%d\n",
            settings.listen_host, settings.listen_port);

    while (1) {
        clilen = sizeof(cli_addr);
        pipe_error = 0;
        pid = 0;
        csock = accept(lsock, 
                       (struct sockaddr *) &cli_addr, 
                       &clilen);
        if (csock < 0) {
            error("ERROR on accept");
            continue;
        }
        handler_msg("got client connection from %s\n",
                    inet_ntoa(cli_addr.sin_addr));

        if (!settings.run_once) {
            handler_msg("forking handler process\n");
            pid = fork();
        }

        if (pid == 0) {  // handler process
            ws_ctx = do_handshake(csock);
            if (settings.run_once) {
                if (ws_ctx == NULL) {
                    // Not a real WebSocket connection
                    continue;
                } else {
                    // Successful connection, stop listening for new
                    // connections
                    close(lsock);
                }
            }
            if (ws_ctx == NULL) {
                handler_msg("No connection after handshake\n");
                break;   // Child process exits
            }

            settings.handler(ws_ctx);
            if (pipe_error) {
                handler_emsg("Closing due to SIGPIPE\n");
            }
            break;   // Child process exits
        } else {         // parent process
            settings.handler_id += 1;
        }
    }
    if (pid == 0) {
        if (ws_ctx) {
            ws_socket_free(ws_ctx);
            free_ws_ctx(ws_ctx);
        } else {
            shutdown(csock, SHUT_RDWR);
            close(csock);
        }
        handler_msg("handler exit\n");
    } else {
        handler_msg("websockify exit\n");
    }

}