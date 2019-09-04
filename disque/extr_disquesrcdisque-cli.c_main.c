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
struct TYPE_2__ {int hostport; int repeat; int interval; int last_cmd_type; int /*<<< orphan*/ * eval; scalar_t__ intrinsic_latency_mode; scalar_t__ scan_mode; scalar_t__ stat_mode; scalar_t__ bigkeys; scalar_t__ pipe_mode; scalar_t__ getrdb_mode; scalar_t__ slave_mode; scalar_t__ latency_mode; void* mb_delim; int /*<<< orphan*/  output; int /*<<< orphan*/ * auth; scalar_t__ stdinarg; int /*<<< orphan*/  pipe_timeout; int /*<<< orphan*/ * rdb_filename; int /*<<< orphan*/ * pattern; scalar_t__ cluster_mode; scalar_t__ latency_history; scalar_t__ pubsub_mode; scalar_t__ monitor_mode; scalar_t__ shutdown; scalar_t__ interactive; scalar_t__ dbnum; int /*<<< orphan*/ * hostsocket; void* hostip; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISQUE_CLI_DEFAULT_PIPE_TIMEOUT ; 
 int /*<<< orphan*/  OUTPUT_RAW ; 
 int /*<<< orphan*/  OUTPUT_STANDARD ; 
 scalar_t__ REDIS_ERR ; 
 scalar_t__ REDIS_OK ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ cliConnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cliInitHelp () ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  convertToSds (int,char**) ; 
 int evalMode (int,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  findBigKeys () ; 
 int /*<<< orphan*/  getRDB () ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  intrinsicLatencyMode () ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latencyMode () ; 
 int noninteractive (int,int /*<<< orphan*/ ) ; 
 int parseOptions (int,char**) ; 
 int /*<<< orphan*/  pipeMode () ; 
 int /*<<< orphan*/  repl () ; 
 int /*<<< orphan*/  scanMode () ; 
 void* sdsnew (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slaveMode () ; 
 int /*<<< orphan*/  statMode () ; 
 int /*<<< orphan*/  stdout ; 

int main(int argc, char **argv) {
    int firstarg;

    config.hostip = sdsnew("127.0.0.1");
    config.hostport = 7711;
    config.hostsocket = NULL;
    config.repeat = 1;
    config.interval = 0;
    config.dbnum = 0;
    config.interactive = 0;
    config.shutdown = 0;
    config.monitor_mode = 0;
    config.pubsub_mode = 0;
    config.latency_mode = 0;
    config.latency_history = 0;
    config.cluster_mode = 0;
    config.slave_mode = 0;
    config.getrdb_mode = 0;
    config.stat_mode = 0;
    config.scan_mode = 0;
    config.intrinsic_latency_mode = 0;
    config.pattern = NULL;
    config.rdb_filename = NULL;
    config.pipe_mode = 0;
    config.pipe_timeout = DISQUE_CLI_DEFAULT_PIPE_TIMEOUT;
    config.bigkeys = 0;
    config.stdinarg = 0;
    config.auth = NULL;
    config.eval = NULL;
    config.last_cmd_type = -1;

    if (!isatty(fileno(stdout)) && (getenv("FAKETTY") == NULL))
        config.output = OUTPUT_RAW;
    else
        config.output = OUTPUT_STANDARD;
    config.mb_delim = sdsnew("\n");
    cliInitHelp();

    firstarg = parseOptions(argc,argv);
    argc -= firstarg;
    argv += firstarg;

    signal(SIGPIPE, SIG_IGN);

    /* Latency mode */
    if (config.latency_mode) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        latencyMode();
    }

    /* Slave mode */
    if (config.slave_mode) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        slaveMode();
    }

    /* Get RDB mode. */
    if (config.getrdb_mode) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        getRDB();
    }

    /* Pipe mode */
    if (config.pipe_mode) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        pipeMode();
    }

    /* Find big keys */
    if (config.bigkeys) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        findBigKeys();
    }

    /* Stat mode */
    if (config.stat_mode) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        if (config.interval == 0) config.interval = 1000000;
        statMode();
    }

    /* Scan mode */
    if (config.scan_mode) {
        if (cliConnect(0) == REDIS_ERR) exit(1);
        scanMode();
    }

    /* Intrinsic latency mode */
    if (config.intrinsic_latency_mode) intrinsicLatencyMode();

    /* Start interactive mode when no command is provided */
    if (argc == 0 && !config.eval) {
        /* Note that in repl mode we don't abort on connection error.
         * A new attempt will be performed for every command send. */
        cliConnect(0);
        repl();
    }

    /* Otherwise, we have some arguments to execute */
    if (cliConnect(0) != REDIS_OK) exit(1);
    if (config.eval) {
        return evalMode(argc,argv);
    } else {
        return noninteractive(argc,convertToSds(argc,argv));
    }
}