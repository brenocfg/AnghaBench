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
struct rewriteConfigState {int dummy; } ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_2__ {int daemonize; int syslog_enabled; scalar_t__ aof_state; int aof_no_fsync_on_rewrite; int activerehashing; int aof_rewrite_incremental_fsync; int aof_load_truncated; int aof_enqueue_jobs_once; int /*<<< orphan*/  configfile; int /*<<< orphan*/  hz; int /*<<< orphan*/  slowlog_max_len; int /*<<< orphan*/  latency_monitor_threshold; int /*<<< orphan*/  slowlog_log_slower_than; int /*<<< orphan*/  cluster_node_timeout; int /*<<< orphan*/  cluster_configfile; int /*<<< orphan*/  aof_rewrite_min_size; int /*<<< orphan*/  aof_rewrite_perc; int /*<<< orphan*/  aof_fsync; int /*<<< orphan*/  aof_filename; int /*<<< orphan*/  maxmemory_samples; int /*<<< orphan*/  maxmemory_policy; int /*<<< orphan*/  maxmemory; int /*<<< orphan*/  maxclients; int /*<<< orphan*/  requirepass; int /*<<< orphan*/  syslog_ident; int /*<<< orphan*/  logfile; int /*<<< orphan*/  verbosity; int /*<<< orphan*/  tcpkeepalive; int /*<<< orphan*/  maxidletime; int /*<<< orphan*/  unixsocketperm; int /*<<< orphan*/  unixsocket; int /*<<< orphan*/  tcp_backlog; int /*<<< orphan*/  port; int /*<<< orphan*/  pidfile; } ;

/* Variables and functions */
 scalar_t__ AOF_OFF ; 
 int /*<<< orphan*/  AOF_REWRITE_MIN_SIZE ; 
 int /*<<< orphan*/  AOF_REWRITE_PERC ; 
 int /*<<< orphan*/  CLUSTER_DEFAULT_NODE_TIMEOUT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_ACTIVE_REHASHING ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_ENQUEUE_JOBS_ONCE ; 
 int /*<<< orphan*/ * CONFIG_DEFAULT_AOF_FILENAME ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_FSYNC ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_LOAD_TRUNCATED ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_NO_FSYNC_ON_REWRITE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_CLIENT_TIMEOUT ; 
 int /*<<< orphan*/ * CONFIG_DEFAULT_CLUSTER_CONFIG_FILE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_HZ ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LATENCY_MONITOR_THRESHOLD ; 
 int /*<<< orphan*/ * CONFIG_DEFAULT_LOGFILE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAXMEMORY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAXMEMORY_POLICY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAXMEMORY_SAMPLES ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAX_CLIENTS ; 
 int /*<<< orphan*/ * CONFIG_DEFAULT_PID_FILE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SERVER_PORT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SLOWLOG_LOG_SLOWER_THAN ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SLOWLOG_MAX_LEN ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SYSLOG_ENABLED ; 
 int /*<<< orphan*/ * CONFIG_DEFAULT_SYSLOG_IDENT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_TCP_BACKLOG ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_TCP_KEEPALIVE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_UNIX_SOCKET_PERM ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_VERBOSITY ; 
 int /*<<< orphan*/  aof_fsync_enum ; 
 int /*<<< orphan*/  loglevel_enum ; 
 int /*<<< orphan*/  maxmemory_policy_enum ; 
 int /*<<< orphan*/  rewriteConfigBindOption (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigBytesOption (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewriteConfigClientoutputbufferlimitOption (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigDirOption (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigEnumOption (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewriteConfigGetContentFromState (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigNumericalOption (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewriteConfigOctalOption (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rewriteConfigOverwriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rewriteConfigState* rewriteConfigReadOldFile (char*) ; 
 int /*<<< orphan*/  rewriteConfigReleaseState (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigRemoveOrphaned (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigStringOption (struct rewriteConfigState*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewriteConfigSyslogfacilityOption (struct rewriteConfigState*) ; 
 int /*<<< orphan*/  rewriteConfigYesNoOption (struct rewriteConfigState*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 

int rewriteConfig(char *path) {
    struct rewriteConfigState *state;
    sds newcontent;
    int retval;

    /* Step 1: read the old config into our rewrite state. */
    if ((state = rewriteConfigReadOldFile(path)) == NULL) return -1;

    /* Step 2: rewrite every single option, replacing or appending it inside
     * the rewrite state. */

    rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
    rewriteConfigStringOption(state,"pidfile",server.pidfile,CONFIG_DEFAULT_PID_FILE);
    rewriteConfigNumericalOption(state,"port",server.port,CONFIG_DEFAULT_SERVER_PORT);
    rewriteConfigNumericalOption(state,"tcp-backlog",server.tcp_backlog,CONFIG_DEFAULT_TCP_BACKLOG);
    rewriteConfigBindOption(state);
    rewriteConfigStringOption(state,"unixsocket",server.unixsocket,NULL);
    rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,CONFIG_DEFAULT_UNIX_SOCKET_PERM);
    rewriteConfigNumericalOption(state,"timeout",server.maxidletime,CONFIG_DEFAULT_CLIENT_TIMEOUT);
    rewriteConfigNumericalOption(state,"tcp-keepalive",server.tcpkeepalive,CONFIG_DEFAULT_TCP_KEEPALIVE);
    rewriteConfigEnumOption(state,"loglevel",server.verbosity,loglevel_enum,CONFIG_DEFAULT_VERBOSITY);
    rewriteConfigStringOption(state,"logfile",server.logfile,CONFIG_DEFAULT_LOGFILE);
    rewriteConfigYesNoOption(state,"syslog-enabled",server.syslog_enabled,CONFIG_DEFAULT_SYSLOG_ENABLED);
    rewriteConfigStringOption(state,"syslog-ident",server.syslog_ident,CONFIG_DEFAULT_SYSLOG_IDENT);
    rewriteConfigSyslogfacilityOption(state);
    rewriteConfigDirOption(state);
    rewriteConfigStringOption(state,"requirepass",server.requirepass,NULL);
    rewriteConfigNumericalOption(state,"maxclients",server.maxclients,CONFIG_DEFAULT_MAX_CLIENTS);
    rewriteConfigBytesOption(state,"maxmemory",server.maxmemory,CONFIG_DEFAULT_MAXMEMORY);
    rewriteConfigEnumOption(state,"maxmemory-policy",server.maxmemory_policy,maxmemory_policy_enum,CONFIG_DEFAULT_MAXMEMORY_POLICY);
    rewriteConfigNumericalOption(state,"maxmemory-samples",server.maxmemory_samples,CONFIG_DEFAULT_MAXMEMORY_SAMPLES);
    rewriteConfigYesNoOption(state,"appendonly",server.aof_state != AOF_OFF,0);
    rewriteConfigStringOption(state,"appendfilename",server.aof_filename,CONFIG_DEFAULT_AOF_FILENAME);
    rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,aof_fsync_enum,CONFIG_DEFAULT_AOF_FSYNC);
    rewriteConfigYesNoOption(state,"no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite,CONFIG_DEFAULT_AOF_NO_FSYNC_ON_REWRITE);
    rewriteConfigNumericalOption(state,"auto-aof-rewrite-percentage",server.aof_rewrite_perc,AOF_REWRITE_PERC);
    rewriteConfigBytesOption(state,"auto-aof-rewrite-min-size",server.aof_rewrite_min_size,AOF_REWRITE_MIN_SIZE);
    rewriteConfigStringOption(state,"cluster-config-file",server.cluster_configfile,CONFIG_DEFAULT_CLUSTER_CONFIG_FILE);
    rewriteConfigNumericalOption(state,"cluster-node-timeout",server.cluster_node_timeout,CLUSTER_DEFAULT_NODE_TIMEOUT);
    rewriteConfigNumericalOption(state,"slowlog-log-slower-than",server.slowlog_log_slower_than,CONFIG_DEFAULT_SLOWLOG_LOG_SLOWER_THAN);
    rewriteConfigNumericalOption(state,"latency-monitor-threshold",server.latency_monitor_threshold,CONFIG_DEFAULT_LATENCY_MONITOR_THRESHOLD);
    rewriteConfigNumericalOption(state,"slowlog-max-len",server.slowlog_max_len,CONFIG_DEFAULT_SLOWLOG_MAX_LEN);
    rewriteConfigYesNoOption(state,"activerehashing",server.activerehashing,CONFIG_DEFAULT_ACTIVE_REHASHING);
    rewriteConfigClientoutputbufferlimitOption(state);
    rewriteConfigNumericalOption(state,"hz",server.hz,CONFIG_DEFAULT_HZ);
    rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
    rewriteConfigYesNoOption(state,"aof-load-truncated",server.aof_load_truncated,CONFIG_DEFAULT_AOF_LOAD_TRUNCATED);
    rewriteConfigYesNoOption(state,"aof-enqueue-jobs-once",server.aof_enqueue_jobs_once,CONFIG_DEFAULT_AOF_ENQUEUE_JOBS_ONCE);

    /* Step 3: remove all the orphaned lines in the old file, that is, lines
     * that were used by a config option and are no longer used, like in case
     * of multiple "save" options or duplicated options. */
    rewriteConfigRemoveOrphaned(state);

    /* Step 4: generate a new configuration file from the modified state
     * and write it into the original file. */
    newcontent = rewriteConfigGetContentFromState(state);
    retval = rewriteConfigOverwriteFile(server.configfile,newcontent);

    sdsfree(newcontent);
    rewriteConfigReleaseState(state);
    return retval;
}