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
typedef  int /*<<< orphan*/ * sds ;
struct TYPE_2__ {int interactive; char* prompt; scalar_t__ cluster_reissue_command; scalar_t__ cluster_mode; void* hostport; int /*<<< orphan*/  hostip; } ;

/* Variables and functions */
 scalar_t__ REDIS_OK ; 
 void* atoi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cliConnect (int) ; 
 int /*<<< orphan*/  cliPrintContextError () ; 
 int /*<<< orphan*/  cliRefreshPrompt () ; 
 scalar_t__ cliSendCommand (int,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  completionCallback ; 
 TYPE_1__ config ; 
 scalar_t__ context ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 char* linenoise (char*) ; 
 int /*<<< orphan*/  linenoiseClearScreen () ; 
 int /*<<< orphan*/  linenoiseHistoryAdd (char*) ; 
 int /*<<< orphan*/  linenoiseHistoryLoad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linenoiseHistorySave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linenoiseSetCompletionCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linenoiseSetMultiLine (int) ; 
 long long mstime () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * sdscatprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfreesplitres (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  sdsnew (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** sdssplitargs (char*,int*) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void repl(void) {
    sds historyfile = NULL;
    int history = 0;
    char *line;
    int argc;
    sds *argv;

    config.interactive = 1;
    linenoiseSetMultiLine(1);
    linenoiseSetCompletionCallback(completionCallback);

    /* Only use history when stdin is a tty. */
    if (isatty(fileno(stdin))) {
        history = 1;

        if (getenv("HOME") != NULL) {
            historyfile = sdscatprintf(sdsempty(),"%s/.disque_history",getenv("HOME"));
            linenoiseHistoryLoad(historyfile);
        }
    }

    cliRefreshPrompt();
    while((line = linenoise(context ? config.prompt : "not connected> ")) != NULL) {
        if (line[0] != '\0') {
            argv = sdssplitargs(line,&argc);
            if (history) linenoiseHistoryAdd(line);
            if (historyfile) linenoiseHistorySave(historyfile);

            if (argv == NULL) {
                printf("Invalid argument(s)\n");
                free(line);
                continue;
            } else if (argc > 0) {
                if (strcasecmp(argv[0],"quit") == 0 ||
                    strcasecmp(argv[0],"exit") == 0)
                {
                    exit(0);
                } else if (argc == 3 && !strcasecmp(argv[0],"connect")) {
                    sdsfree(config.hostip);
                    config.hostip = sdsnew(argv[1]);
                    config.hostport = atoi(argv[2]);
                    cliRefreshPrompt();
                    cliConnect(1);
                } else if (argc == 1 && !strcasecmp(argv[0],"clear")) {
                    linenoiseClearScreen();
                } else {
                    long long start_time = mstime(), elapsed;
                    int repeat, skipargs = 0;

                    repeat = atoi(argv[0]);
                    if (argc > 1 && repeat) {
                        skipargs = 1;
                    } else {
                        repeat = 1;
                    }

                    while (1) {
                        config.cluster_reissue_command = 0;
                        if (cliSendCommand(argc-skipargs,argv+skipargs,repeat)
                            != REDIS_OK)
                        {
                            cliConnect(1);

                            /* If we still cannot send the command print error.
                             * We'll try to reconnect the next time. */
                            if (cliSendCommand(argc-skipargs,argv+skipargs,repeat)
                                != REDIS_OK)
                                cliPrintContextError();
                        }
                        /* Issue the command again if we got redirected in cluster mode */
                        if (config.cluster_mode && config.cluster_reissue_command) {
                            cliConnect(1);
                        } else {
                            break;
                        }
                    }
                    elapsed = mstime()-start_time;
                    if (elapsed >= 500) {
                        printf("(%.2fs)\n",(double)elapsed/1000);
                    }
                }
            }
            /* Free the argument vector */
            sdsfreesplitres(argv,argc);
        }
        /* linenoise() returns malloc-ed lines like readline() */
        free(line);
    }
    exit(0);
}