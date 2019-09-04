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
struct TYPE_2__ {char* runid; char* jobid_seed; int arch_bits; int sofd; int active_expire_enabled; int aof_rewrite_time_last; int aof_rewrite_time_start; int aof_fd; int aof_selected_db; int next_client_id; int loading_process_events_interval_bytes; char* assert_failed; char* assert_file; scalar_t__ watchdog_period; scalar_t__ bug_report_start; scalar_t__ assert_line; int /*<<< orphan*/  latency_monitor_threshold; int /*<<< orphan*/  slowlog_max_len; int /*<<< orphan*/  slowlog_log_slower_than; void* rpopCommand; void* lpopCommand; void* lpushCommand; void* multiCommand; void* delCommand; void* orig_commands; void* commands; int /*<<< orphan*/ * client_obuf_limits; void* cluster_configfile; int /*<<< orphan*/  cluster_node_timeout; scalar_t__ shutdown_asap; int /*<<< orphan*/  maxmemory_samples; int /*<<< orphan*/  maxmemory_policy; int /*<<< orphan*/  maxmemory; scalar_t__ bpop_blocked_clients; int /*<<< orphan*/  maxclients; int /*<<< orphan*/  activerehashing; int /*<<< orphan*/ * requirepass; void* aof_filename; void* pidfile; int /*<<< orphan*/  aof_enqueue_jobs_once; int /*<<< orphan*/  aof_load_truncated; int /*<<< orphan*/  aof_rewrite_incremental_fsync; scalar_t__ aof_flush_postponed_start; scalar_t__ aof_delayed_fsync; int /*<<< orphan*/  aof_lastbgrewrite_status; int /*<<< orphan*/  aof_last_fsync; scalar_t__ aof_rewrite_scheduled; scalar_t__ aof_rewrite_base_size; int /*<<< orphan*/  aof_rewrite_min_size; int /*<<< orphan*/  aof_rewrite_perc; int /*<<< orphan*/  aof_no_fsync_on_rewrite; int /*<<< orphan*/  aof_fsync; int /*<<< orphan*/  aof_state; int /*<<< orphan*/  daemonize; int /*<<< orphan*/  syslog_facility; void* syslog_ident; int /*<<< orphan*/  syslog_enabled; void* logfile; scalar_t__ loading; int /*<<< orphan*/  client_max_querybuf_len; int /*<<< orphan*/  tcpkeepalive; int /*<<< orphan*/  maxidletime; int /*<<< orphan*/  verbosity; int /*<<< orphan*/  dbnum; scalar_t__ ipfd_count; int /*<<< orphan*/  unixsocketperm; int /*<<< orphan*/ * unixsocket; scalar_t__ bindaddr_count; int /*<<< orphan*/  tcp_backlog; int /*<<< orphan*/  port; int /*<<< orphan*/  hz; int /*<<< orphan*/ * executable; int /*<<< orphan*/ * configfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOF_OFF ; 
 int /*<<< orphan*/  AOF_REWRITE_MIN_SIZE ; 
 int /*<<< orphan*/  AOF_REWRITE_PERC ; 
 int CLIENT_TYPE_COUNT ; 
 int /*<<< orphan*/  CLUSTER_DEFAULT_NODE_TIMEOUT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_ACTIVE_REHASHING ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_ENQUEUE_JOBS_ONCE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_FILENAME ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_FSYNC ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_LOAD_TRUNCATED ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_NO_FSYNC_ON_REWRITE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_CLIENT_TIMEOUT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_CLUSTER_CONFIG_FILE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_DAEMONIZE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_DBNUM ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_HZ ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LATENCY_MONITOR_THRESHOLD ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_LOGFILE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAXMEMORY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAXMEMORY_POLICY ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAXMEMORY_SAMPLES ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_MAX_CLIENTS ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_PID_FILE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SERVER_PORT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SLOWLOG_LOG_SLOWER_THAN ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SLOWLOG_MAX_LEN ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SYSLOG_ENABLED ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_SYSLOG_IDENT ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_TCP_BACKLOG ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_TCP_KEEPALIVE ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_UNIX_SOCKET_PERM ; 
 int /*<<< orphan*/  CONFIG_DEFAULT_VERBOSITY ; 
 size_t CONFIG_RUN_ID_SIZE ; 
 int /*<<< orphan*/  C_OK ; 
 int /*<<< orphan*/  LOG_LOCAL0 ; 
 int /*<<< orphan*/  PROTO_MAX_QUERYBUF_LEN ; 
 double R_Nan ; 
 double R_NegInf ; 
 double R_PosInf ; 
 double R_Zero ; 
 int /*<<< orphan*/ * clientBufferLimitsDefaults ; 
 int /*<<< orphan*/  commandTableDictType ; 
 void* dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getRandomHexChars (char*,size_t) ; 
 void* lookupCommandByCString (char*) ; 
 int /*<<< orphan*/  populateCommandTable () ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 void* zstrdup (int /*<<< orphan*/ ) ; 

void initServerConfig(void) {
    int j;

    getRandomHexChars(server.runid,CONFIG_RUN_ID_SIZE);
    getRandomHexChars(server.jobid_seed,CONFIG_RUN_ID_SIZE);
    server.configfile = NULL;
    server.executable = NULL;
    server.hz = CONFIG_DEFAULT_HZ;
    server.runid[CONFIG_RUN_ID_SIZE] = '\0';
    server.arch_bits = (sizeof(long) == 8) ? 64 : 32;
    server.port = CONFIG_DEFAULT_SERVER_PORT;
    server.tcp_backlog = CONFIG_DEFAULT_TCP_BACKLOG;
    server.bindaddr_count = 0;
    server.unixsocket = NULL;
    server.unixsocketperm = CONFIG_DEFAULT_UNIX_SOCKET_PERM;
    server.ipfd_count = 0;
    server.sofd = -1;
    server.dbnum = CONFIG_DEFAULT_DBNUM;
    server.verbosity = CONFIG_DEFAULT_VERBOSITY;
    server.maxidletime = CONFIG_DEFAULT_CLIENT_TIMEOUT;
    server.tcpkeepalive = CONFIG_DEFAULT_TCP_KEEPALIVE;
    server.active_expire_enabled = 1;
    server.client_max_querybuf_len = PROTO_MAX_QUERYBUF_LEN;
    server.loading = 0;
    server.logfile = zstrdup(CONFIG_DEFAULT_LOGFILE);
    server.syslog_enabled = CONFIG_DEFAULT_SYSLOG_ENABLED;
    server.syslog_ident = zstrdup(CONFIG_DEFAULT_SYSLOG_IDENT);
    server.syslog_facility = LOG_LOCAL0;
    server.daemonize = CONFIG_DEFAULT_DAEMONIZE;
    server.aof_state = AOF_OFF;
    server.aof_fsync = CONFIG_DEFAULT_AOF_FSYNC;
    server.aof_no_fsync_on_rewrite = CONFIG_DEFAULT_AOF_NO_FSYNC_ON_REWRITE;
    server.aof_rewrite_perc = AOF_REWRITE_PERC;
    server.aof_rewrite_min_size = AOF_REWRITE_MIN_SIZE;
    server.aof_rewrite_base_size = 0;
    server.aof_rewrite_scheduled = 0;
    server.aof_last_fsync = time(NULL);
    server.aof_rewrite_time_last = -1;
    server.aof_rewrite_time_start = -1;
    server.aof_lastbgrewrite_status = C_OK;
    server.aof_delayed_fsync = 0;
    server.aof_fd = -1;
    server.aof_selected_db = -1; /* Make sure the first time will not match */
    server.aof_flush_postponed_start = 0;
    server.aof_rewrite_incremental_fsync = CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC;
    server.aof_load_truncated = CONFIG_DEFAULT_AOF_LOAD_TRUNCATED;
    server.aof_enqueue_jobs_once = CONFIG_DEFAULT_AOF_ENQUEUE_JOBS_ONCE;
    server.pidfile = zstrdup(CONFIG_DEFAULT_PID_FILE);
    server.aof_filename = zstrdup(CONFIG_DEFAULT_AOF_FILENAME);
    server.requirepass = NULL;
    server.activerehashing = CONFIG_DEFAULT_ACTIVE_REHASHING;
    server.maxclients = CONFIG_DEFAULT_MAX_CLIENTS;
    server.bpop_blocked_clients = 0;
    server.maxmemory = CONFIG_DEFAULT_MAXMEMORY;
    server.maxmemory_policy = CONFIG_DEFAULT_MAXMEMORY_POLICY;
    server.maxmemory_samples = CONFIG_DEFAULT_MAXMEMORY_SAMPLES;
    server.shutdown_asap = 0;
    server.cluster_node_timeout = CLUSTER_DEFAULT_NODE_TIMEOUT;
    server.cluster_configfile = zstrdup(CONFIG_DEFAULT_CLUSTER_CONFIG_FILE);
    server.next_client_id = 1; /* Client IDs, start from 1 .*/
    server.loading_process_events_interval_bytes = (1024*1024*2);

    /* Client output buffer limits */
    for (j = 0; j < CLIENT_TYPE_COUNT; j++)
        server.client_obuf_limits[j] = clientBufferLimitsDefaults[j];

    /* Double constants initialization */
    R_Zero = 0.0;
    R_PosInf = 1.0/R_Zero;
    R_NegInf = -1.0/R_Zero;
    R_Nan = R_Zero/R_Zero;

    /* Command table -- we initiialize it here as it is part of the
     * initial configuration, since command names may be changed via
     * disque.conf using the rename-command directive. */
    server.commands = dictCreate(&commandTableDictType,NULL);
    server.orig_commands = dictCreate(&commandTableDictType,NULL);
    populateCommandTable();
    server.delCommand = lookupCommandByCString("del");
    server.multiCommand = lookupCommandByCString("multi");
    server.lpushCommand = lookupCommandByCString("lpush");
    server.lpopCommand = lookupCommandByCString("lpop");
    server.rpopCommand = lookupCommandByCString("rpop");

    /* Slow log */
    server.slowlog_log_slower_than = CONFIG_DEFAULT_SLOWLOG_LOG_SLOWER_THAN;
    server.slowlog_max_len = CONFIG_DEFAULT_SLOWLOG_MAX_LEN;

    /* Latency monitor */
    server.latency_monitor_threshold = CONFIG_DEFAULT_LATENCY_MONITOR_THRESHOLD;

    /* Debugging */
    server.assert_failed = "<no assertion failed>";
    server.assert_file = "<no file>";
    server.assert_line = 0;
    server.bug_report_start = 0;
    server.watchdog_period = 0;
}