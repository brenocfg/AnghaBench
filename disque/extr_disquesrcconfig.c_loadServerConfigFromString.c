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
struct serverCommand {int dummy; } ;
typedef  char* sds ;
typedef  int mode_t ;
struct TYPE_4__ {scalar_t__ maxidletime; scalar_t__ tcpkeepalive; int port; scalar_t__ tcp_backlog; int bindaddr_count; int unixsocketperm; scalar_t__ verbosity; char* logfile; int syslog_enabled; char* syslog_ident; scalar_t__ syslog_facility; int dbnum; int maxclients; long long maxmemory; scalar_t__ maxmemory_policy; scalar_t__ maxmemory_samples; int activerehashing; int daemonize; scalar_t__ hz; char* aof_filename; int aof_no_fsync_on_rewrite; scalar_t__ aof_fsync; scalar_t__ aof_rewrite_perc; int aof_rewrite_incremental_fsync; int aof_load_truncated; int aof_enqueue_jobs_once; char* pidfile; char* cluster_configfile; scalar_t__ cluster_node_timeout; scalar_t__ latency_monitor_threshold; TYPE_1__* client_obuf_limits; void* slowlog_max_len; void* slowlog_log_slower_than; int /*<<< orphan*/  commands; void* requirepass; void* aof_rewrite_min_size; int /*<<< orphan*/  aof_state; void* unixsocket; void** bindaddr; } ;
struct TYPE_3__ {unsigned long long hard_limit_bytes; unsigned long long soft_limit_bytes; int soft_limit_seconds; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AOF_OFF ; 
 int /*<<< orphan*/  AOF_ON ; 
 scalar_t__ CONFIG_AUTHPASS_MAX_LEN ; 
 int CONFIG_BINDADDR_MAX ; 
 scalar_t__ CONFIG_MAX_HZ ; 
 scalar_t__ CONFIG_MIN_HZ ; 
 int DICT_OK ; 
 scalar_t__ INT_MIN ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  aof_fsync_enum ; 
 void* atoi (char*) ; 
 int chdir (char*) ; 
 void* configEnumGetValue (int /*<<< orphan*/ ,char*) ; 
 int dictAdd (int /*<<< orphan*/ ,char*,struct serverCommand*) ; 
 int dictDelete (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getClientTypeByName (char*) ; 
 int /*<<< orphan*/  loadServerConfig (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  loglevel_enum ; 
 struct serverCommand* lookupCommand (char*) ; 
 int /*<<< orphan*/  maxmemory_policy_enum ; 
 void* memtoll (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pathIsBaseName (char*) ; 
 char* sdscatprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* sdsdup (char*) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 int /*<<< orphan*/  sdsfreesplitres (char**,int) ; 
 scalar_t__ sdslen (char*) ; 
 char** sdssplitargs (char*,int*) ; 
 char** sdssplitlen (char*,scalar_t__,char*,int,int*) ; 
 int /*<<< orphan*/  sdstolower (char*) ; 
 char* sdstrim (char*,char*) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 
 void* strtoll (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  syslog_facility_enum ; 
 int yesnotoi (char*) ; 
 int /*<<< orphan*/  zfree (char*) ; 
 void* zstrdup (char*) ; 

void loadServerConfigFromString(char *config) {
    char *err = NULL;
    int linenum = 0, totlines, i;
    sds *lines;

    lines = sdssplitlen(config,strlen(config),"\n",1,&totlines);

    for (i = 0; i < totlines; i++) {
        sds *argv;
        int argc;

        linenum = i+1;
        lines[i] = sdstrim(lines[i]," \t\r\n");

        /* Skip comments and blank lines */
        if (lines[i][0] == '#' || lines[i][0] == '\0') continue;

        /* Split into arguments */
        argv = sdssplitargs(lines[i],&argc);
        if (argv == NULL) {
            err = "Unbalanced quotes in configuration line";
            goto loaderr;
        }

        /* Skip this line if the resulting command vector is empty. */
        if (argc == 0) {
            sdsfreesplitres(argv,argc);
            continue;
        }
        sdstolower(argv[0]);

        /* Execute config directives */
        if (!strcasecmp(argv[0],"timeout") && argc == 2) {
            server.maxidletime = atoi(argv[1]);
            if (server.maxidletime < 0) {
                err = "Invalid timeout value"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"tcp-keepalive") && argc == 2) {
            server.tcpkeepalive = atoi(argv[1]);
            if (server.tcpkeepalive < 0) {
                err = "Invalid tcp-keepalive value"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"port") && argc == 2) {
            server.port = atoi(argv[1]);
            if (server.port < 0 || server.port > 65535) {
                err = "Invalid port"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"tcp-backlog") && argc == 2) {
            server.tcp_backlog = atoi(argv[1]);
            if (server.tcp_backlog < 0) {
                err = "Invalid backlog value"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"bind") && argc >= 2) {
            int j, addresses = argc-1;

            if (addresses > CONFIG_BINDADDR_MAX) {
                err = "Too many bind addresses specified"; goto loaderr;
            }
            for (j = 0; j < addresses; j++)
                server.bindaddr[j] = zstrdup(argv[j+1]);
            server.bindaddr_count = addresses;
        } else if (!strcasecmp(argv[0],"unixsocket") && argc == 2) {
            server.unixsocket = zstrdup(argv[1]);
        } else if (!strcasecmp(argv[0],"unixsocketperm") && argc == 2) {
            errno = 0;
            server.unixsocketperm = (mode_t)strtol(argv[1], NULL, 8);
            if (errno || server.unixsocketperm > 0777) {
                err = "Invalid socket file permissions"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"dir") && argc == 2) {
            if (chdir(argv[1]) == -1) {
                serverLog(LL_WARNING,"Can't chdir to '%s': %s",
                    argv[1], strerror(errno));
                exit(1);
            }
        } else if (!strcasecmp(argv[0],"loglevel") && argc == 2) {
            server.verbosity = configEnumGetValue(loglevel_enum,argv[1]);
            if (server.verbosity == INT_MIN) {
                err = "Invalid log level. "
                      "Must be one of debug, verbose, notice, warning";
                goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"logfile") && argc == 2) {
            FILE *logfp;

            zfree(server.logfile);
            server.logfile = zstrdup(argv[1]);
            if (server.logfile[0] != '\0') {
                /* Test if we are able to open the file. The server will not
                 * be able to abort just for this problem later... */
                logfp = fopen(server.logfile,"a");
                if (logfp == NULL) {
                    err = sdscatprintf(sdsempty(),
                        "Can't open the log file: %s", strerror(errno));
                    goto loaderr;
                }
                fclose(logfp);
            }
        } else if (!strcasecmp(argv[0],"syslog-enabled") && argc == 2) {
            if ((server.syslog_enabled = yesnotoi(argv[1])) == -1) {
                err = "argument must be 'yes' or 'no'"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"syslog-ident") && argc == 2) {
            if (server.syslog_ident) zfree(server.syslog_ident);
            server.syslog_ident = zstrdup(argv[1]);
        } else if (!strcasecmp(argv[0],"syslog-facility") && argc == 2) {
            server.syslog_facility =
                configEnumGetValue(syslog_facility_enum,argv[1]);
            if (server.syslog_facility == INT_MIN) {
                err = "Invalid log facility. Must be one of USER or between LOCAL0-LOCAL7";
                goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"databases") && argc == 2) {
            server.dbnum = atoi(argv[1]);
            if (server.dbnum < 1) {
                err = "Invalid number of databases"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"include") && argc == 2) {
            loadServerConfig(argv[1],NULL);
        } else if (!strcasecmp(argv[0],"maxclients") && argc == 2) {
            server.maxclients = atoi(argv[1]);
            if (server.maxclients < 1) {
                err = "Invalid max clients limit"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"maxmemory") && argc == 2) {
            /* To check for negative values, we need a long long first */
            long long maxmemory = memtoll(argv[1],NULL);
            server.maxmemory = maxmemory;
            if (maxmemory <= 0) {
                err = "You need to specify a memory limit greater than zero"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"maxmemory-policy") && argc == 2) {
            server.maxmemory_policy =
                configEnumGetValue(maxmemory_policy_enum,argv[1]);
            if (server.maxmemory_policy == INT_MIN) {
                 err = "Invalid maxmemory policy";
                 goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"maxmemory-samples") && argc == 2) {
            server.maxmemory_samples = atoi(argv[1]);
            if (server.maxmemory_samples <= 0) {
                err = "maxmemory-samples must be 1 or greater";
                goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"activerehashing") && argc == 2) {
            if ((server.activerehashing = yesnotoi(argv[1])) == -1) {
                err = "argument must be 'yes' or 'no'"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"daemonize") && argc == 2) {
            if ((server.daemonize = yesnotoi(argv[1])) == -1) {
                err = "argument must be 'yes' or 'no'"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"hz") && argc == 2) {
            server.hz = atoi(argv[1]);
            if (server.hz < CONFIG_MIN_HZ) server.hz = CONFIG_MIN_HZ;
            if (server.hz > CONFIG_MAX_HZ) server.hz = CONFIG_MAX_HZ;
        } else if (!strcasecmp(argv[0],"appendonly") && argc == 2) {
            int yes;

            if ((yes = yesnotoi(argv[1])) == -1) {
                err = "argument must be 'yes' or 'no'"; goto loaderr;
            }
            server.aof_state = yes ? AOF_ON : AOF_OFF;
        } else if (!strcasecmp(argv[0],"appendfilename") && argc == 2) {
            if (!pathIsBaseName(argv[1])) {
                err = "appendfilename can't be a path, just a filename";
                goto loaderr;
            }
            zfree(server.aof_filename);
            server.aof_filename = zstrdup(argv[1]);
        } else if (!strcasecmp(argv[0],"no-appendfsync-on-rewrite")
                   && argc == 2) {
            if ((server.aof_no_fsync_on_rewrite= yesnotoi(argv[1])) == -1) {
                err = "argument must be 'yes' or 'no'"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"appendfsync") && argc == 2) {
            server.aof_fsync = configEnumGetValue(aof_fsync_enum,argv[1]);
            if (server.aof_fsync == INT_MIN) {
                err = "argument must be 'no', 'always' or 'everysec'";
                goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"auto-aof-rewrite-percentage") &&
                   argc == 2)
        {
            server.aof_rewrite_perc = atoi(argv[1]);
            if (server.aof_rewrite_perc < 0) {
                err = "Invalid negative percentage for AOF auto rewrite";
                goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"auto-aof-rewrite-min-size") &&
                   argc == 2)
        {
            server.aof_rewrite_min_size = memtoll(argv[1],NULL);
        } else if (!strcasecmp(argv[0],"aof-rewrite-incremental-fsync") &&
                   argc == 2)
        {
            if ((server.aof_rewrite_incremental_fsync =
                 yesnotoi(argv[1])) == -1) {
                err = "argument must be 'yes' or 'no'"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"aof-load-truncated") && argc == 2) {
            if ((server.aof_load_truncated = yesnotoi(argv[1])) == -1) {
                err = "argument must be 'yes' or 'no'"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"aof-enqueue-jobs-once") && argc == 2) {
            if ((server.aof_enqueue_jobs_once = yesnotoi(argv[1])) == -1) {
                err = "argument must be 'yes' or 'no'"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"requirepass") && argc == 2) {
            if (strlen(argv[1]) > CONFIG_AUTHPASS_MAX_LEN) {
                err = "Password is longer than CONFIG_AUTHPASS_MAX_LEN";
                goto loaderr;
            }
            server.requirepass = zstrdup(argv[1]);
        } else if (!strcasecmp(argv[0],"pidfile") && argc == 2) {
            zfree(server.pidfile);
            server.pidfile = zstrdup(argv[1]);
        } else if (!strcasecmp(argv[0],"rename-command") && argc == 3) {
            struct serverCommand *cmd = lookupCommand(argv[1]);
            int retval;

            if (!cmd) {
                err = "No such command in rename-command";
                goto loaderr;
            }

            /* If the target command name is the empty string we just
             * remove it from the command table. */
            retval = dictDelete(server.commands, argv[1]);
            serverAssert(retval == DICT_OK);

            /* Otherwise we re-add the command under a different name. */
            if (sdslen(argv[2]) != 0) {
                sds copy = sdsdup(argv[2]);

                retval = dictAdd(server.commands, copy, cmd);
                if (retval != DICT_OK) {
                    sdsfree(copy);
                    err = "Target command name already exists"; goto loaderr;
                }
            }
        } else if (!strcasecmp(argv[0],"cluster-config-file") && argc == 2) {
            zfree(server.cluster_configfile);
            server.cluster_configfile = zstrdup(argv[1]);
        } else if (!strcasecmp(argv[0],"cluster-node-timeout") && argc == 2) {
            server.cluster_node_timeout = strtoll(argv[1],NULL,10);
            if (server.cluster_node_timeout <= 0) {
                err = "cluster node timeout must be 1 or greater"; goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"slowlog-log-slower-than") &&
                   argc == 2)
        {
            server.slowlog_log_slower_than = strtoll(argv[1],NULL,10);
        } else if (!strcasecmp(argv[0],"latency-monitor-threshold") &&
                   argc == 2)
        {
            server.latency_monitor_threshold = strtoll(argv[1],NULL,10);
            if (server.latency_monitor_threshold < 0) {
                err = "The latency threshold can't be negative";
                goto loaderr;
            }
        } else if (!strcasecmp(argv[0],"slowlog-max-len") && argc == 2) {
            server.slowlog_max_len = strtoll(argv[1],NULL,10);
        } else if (!strcasecmp(argv[0],"client-output-buffer-limit") &&
                   argc == 5)
        {
            int class = getClientTypeByName(argv[1]);
            unsigned long long hard, soft;
            int soft_seconds;

            if (class == -1) {
                err = "Unrecognized client limit class";
                goto loaderr;
            }
            hard = memtoll(argv[2],NULL);
            soft = memtoll(argv[3],NULL);
            soft_seconds = atoi(argv[4]);
            if (soft_seconds < 0) {
                err = "Negative number of seconds in soft limit is invalid";
                goto loaderr;
            }
            server.client_obuf_limits[class].hard_limit_bytes = hard;
            server.client_obuf_limits[class].soft_limit_bytes = soft;
            server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
        } else {
            err = "Bad directive or wrong number of arguments"; goto loaderr;
        }
        sdsfreesplitres(argv,argc);
    }

    sdsfreesplitres(lines,totlines);
    return;

loaderr:
    fprintf(stderr, "\n*** FATAL CONFIG FILE ERROR ***\n");
    fprintf(stderr, "Reading the configuration file, at line %d\n", linenum);
    fprintf(stderr, ">>> '%s'\n", lines[i]);
    fprintf(stderr, "%s\n", err);
    exit(1);
}