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
struct TYPE_2__ {int shutdown; int monitor_mode; int pubsub_mode; int slave_mode; scalar_t__ output; scalar_t__ interval; int /*<<< orphan*/  dbnum; } ;

/* Variables and functions */
 scalar_t__ OUTPUT_RAW ; 
 int REDIS_ERR ; 
 int REDIS_OK ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  cliOutputHelp (int,char**) ; 
 int cliReadReply (int) ; 
 int /*<<< orphan*/  cliRefreshPrompt () ; 
 int /*<<< orphan*/  cliSelect () ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/ * context ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (size_t*) ; 
 size_t* malloc (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  redisAppendCommandArgv (int /*<<< orphan*/ *,int,char const**,size_t*) ; 
 size_t sdslen (char*) ; 
 int /*<<< orphan*/  slaveMode () ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  usleep (scalar_t__) ; 

__attribute__((used)) static int cliSendCommand(int argc, char **argv, int repeat) {
    char *command = argv[0];
    size_t *argvlen;
    int j, output_raw;

    if (!strcasecmp(command,"help") || !strcasecmp(command,"?")) {
        cliOutputHelp(--argc, ++argv);
        return REDIS_OK;
    }

    if (context == NULL) return REDIS_ERR;

    output_raw = 0;
    if (!strcasecmp(command,"info") ||
        (argc == 2 && !strcasecmp(command,"cluster") &&
                      (!strcasecmp(argv[1],"nodes") ||
                       !strcasecmp(argv[1],"info"))) ||
        (argc == 2 && !strcasecmp(command,"client") &&
                       !strcasecmp(argv[1],"list")) ||
        (argc == 3 && !strcasecmp(command,"latency") &&
                       !strcasecmp(argv[1],"graph")) ||
        (argc == 2 && !strcasecmp(command,"latency") &&
                       !strcasecmp(argv[1],"doctor")))
    {
        output_raw = 1;
    }

    if (!strcasecmp(command,"shutdown")) config.shutdown = 1;
    if (!strcasecmp(command,"monitor")) config.monitor_mode = 1;
    if (!strcasecmp(command,"subscribe") ||
        !strcasecmp(command,"psubscribe")) config.pubsub_mode = 1;
    if (!strcasecmp(command,"sync") ||
        !strcasecmp(command,"psync")) config.slave_mode = 1;

    /* Setup argument length */
    argvlen = malloc(argc*sizeof(size_t));
    for (j = 0; j < argc; j++)
        argvlen[j] = sdslen(argv[j]);

    while(repeat--) {
        redisAppendCommandArgv(context,argc,(const char**)argv,argvlen);
        while (config.monitor_mode) {
            if (cliReadReply(output_raw) != REDIS_OK) exit(1);
            fflush(stdout);
        }

        if (config.pubsub_mode) {
            if (config.output != OUTPUT_RAW)
                printf("Reading messages... (press Ctrl-C to quit)\n");
            while (1) {
                if (cliReadReply(output_raw) != REDIS_OK) exit(1);
            }
        }

        if (config.slave_mode) {
            printf("Entering slave output mode...  (press Ctrl-C to quit)\n");
            slaveMode();
            config.slave_mode = 0;
            free(argvlen);
            return REDIS_ERR;  /* Error = slaveMode lost connection to master */
        }

        if (cliReadReply(output_raw) != REDIS_OK) {
            free(argvlen);
            return REDIS_ERR;
        } else {
            /* Store database number when SELECT was successfully executed. */
            if (!strcasecmp(command,"select") && argc == 2) {
                config.dbnum = atoi(argv[1]);
                cliRefreshPrompt();
            } else if (!strcasecmp(command,"auth") && argc == 2) {
                cliSelect();
            }
        }
        if (config.interval) usleep(config.interval);
        fflush(stdout); /* Make it grep friendly */
    }

    free(argvlen);
    return REDIS_OK;
}