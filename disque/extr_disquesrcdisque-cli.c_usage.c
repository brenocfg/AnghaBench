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
typedef  char* sds ;

/* Variables and functions */
 int DISQUE_CLI_DEFAULT_PIPE_TIMEOUT ; 
 char* cliVersion () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(void) {
    sds version = cliVersion();
    fprintf(stderr,
"disque %s\n"
"\n"
"Usage: disque [OPTIONS] [cmd [arg [arg ...]]]\n"
"  -h <hostname>      Server hostname (default: 127.0.0.1).\n"
"  -p <port>          Server port (default: 7711).\n"
"  -s <socket>        Server socket (overrides hostname and port).\n"
"  -a <password>      Password to use when connecting to the server.\n"
"  -r <repeat>        Execute specified command N times.\n"
"  -i <interval>      When -r is used, waits <interval> seconds per command.\n"
"                     It is possible to specify sub-second times like -i 0.1.\n"
"  -n <db>            Database number.\n"
"  -x                 Read last argument from STDIN.\n"
"  -d <delimiter>     Multi-bulk delimiter in for raw formatting (default: \\n).\n"
"  -c                 Enable cluster mode (follow -ASK and -MOVED redirections).\n"
"  --raw              Use raw formatting for replies (default when STDOUT is\n"
"                     not a tty).\n"
"  --no-raw           Force formatted output even when STDOUT is not a tty.\n"
"  --csv              Output in CSV format.\n"
"  --latency          Enter a special mode continuously sampling latency.\n"
"  --latency-history  Like --latency but tracking latency changes over time.\n"
"                     Default time interval is 15 sec. Change it using -i.\n"
"  --slave            Simulate a slave showing commands received from the master.\n"
"  --rdb <filename>   Transfer an RDB dump from remote server to local file.\n"
"  --pipe             Transfer raw Disque protocol from stdin to server.\n"
"  --pipe-timeout <n> In --pipe mode, abort with error if after sending all data.\n"
"                     no reply is received within <n> seconds.\n"
"                     Default timeout: %d. Use 0 to wait forever.\n"
"  --bigkeys          Sample Disque keys looking for big keys.\n"
"  --scan             List all keys using the SCAN command.\n"
"  --pattern <pat>    Useful with --scan to specify a SCAN pattern.\n"
"  --intrinsic-latency <sec> Run a test to measure intrinsic system latency.\n"
"                     The test will run for the specified amount of seconds.\n"
"  --eval <file>      Send an EVAL command using the Lua script at <file>.\n"
"  --help             Output this help and exit.\n"
"  --version          Output version and exit.\n"
"\n"
"Examples:\n"
"  cat /etc/passwd | disque -x set mypasswd\n"
"  disque get mypasswd\n"
"  disque -r 100 lpush mylist x\n"
"  disque -r 100 -i 1 info | grep used_memory_human:\n"
"  disque --eval myscript.lua key1 key2 , arg1 arg2 arg3\n"
"  disque --scan --pattern '*:12345*'\n"
"\n"
"  (Note: when using --eval the comma separates KEYS[] from ARGV[] items)\n"
"\n"
"When no command is given, disque starts in interactive mode.\n"
"Type \"help\" in interactive mode for information on available commands.\n"
"\n",
        version, DISQUE_CLI_DEFAULT_PIPE_TIMEOUT);
    sdsfree(version);
    exit(1);
}