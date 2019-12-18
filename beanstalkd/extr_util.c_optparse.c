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
typedef  int int64 ;
struct TYPE_4__ {int syncrate; int wantsync; int use; void* dir; void* filesize; } ;
struct TYPE_5__ {TYPE_1__ wal; void* user; void* addr; void* port; } ;
typedef  TYPE_2__ Server ;

/* Variables and functions */
 void* EARGF (int /*<<< orphan*/ ) ; 
 char* JOB_DATA_SIZE_LIMIT_MAX ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flagusage (char*) ; 
 char* job_data_size_limit ; 
 void* parse_size_t (void*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  usage (int) ; 
 int /*<<< orphan*/  verbose ; 
 char* version ; 
 int /*<<< orphan*/  warn_systemd_ignored_option (char*,void*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

void
optparse(Server *s, char **argv)
{
    int64 ms;
    char *arg, *tmp;
#   define EARGF(x) (*arg ? (tmp=arg,arg="",tmp) : *argv ? *argv++ : (x))

    while ((arg = *argv++) && *arg++ == '-' && *arg) {
        char c;
        while ((c = *arg++)) {
            switch (c) {
                case 'p':
                    s->port = EARGF(flagusage("-p"));
                    warn_systemd_ignored_option("-p", s->port);
                    break;
                case 'l':
                    s->addr = EARGF(flagusage("-l"));
                    warn_systemd_ignored_option("-l", s->addr);
                    break;
                case 'z':
                    job_data_size_limit = parse_size_t(EARGF(flagusage("-z")));
                    if (job_data_size_limit > JOB_DATA_SIZE_LIMIT_MAX) {
                        warnx("maximum job size was set to %d", JOB_DATA_SIZE_LIMIT_MAX);
                        job_data_size_limit = JOB_DATA_SIZE_LIMIT_MAX;
                    }
                    break;
                case 's':
                    s->wal.filesize = parse_size_t(EARGF(flagusage("-s")));
                    break;
                case 'c':
                    warnx("-c flag was removed. binlog is always compacted.");
                    break;
                case 'n':
                    warnx("-n flag was removed. binlog is always compacted.");
                    break;
                case 'f':
                    ms = (int64)parse_size_t(EARGF(flagusage("-f")));
                    s->wal.syncrate = ms * 1000000;
                    s->wal.wantsync = 1;
                    break;
                case 'F':
                    s->wal.wantsync = 0;
                    break;
                case 'u':
                    s->user = EARGF(flagusage("-u"));
                    break;
                case 'b':
                    s->wal.dir = EARGF(flagusage("-b"));
                    s->wal.use = 1;
                    break;
                case 'h':
                    usage(0);
                case 'v':
                    printf("beanstalkd %s\n", version);
                    exit(0);
                case 'V':
                    verbose++;
                    break;
                default:
                    warnx("unknown flag: %s", arg-2);
                    usage(5);
            }
        }
    }
    if (arg) {
        warnx("unknown argument: %s", arg-1);
        usage(5);
    }
}