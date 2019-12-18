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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int output; } ;
struct TYPE_3__ {int fd; } ;

/* Variables and functions */
 int OUTPUT_CSV ; 
 scalar_t__ REDIS_OK ; 
 scalar_t__ cliReadReply (int /*<<< orphan*/ ) ; 
 TYPE_2__ config ; 
 TYPE_1__* context ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ read (int,char*,int) ; 
 unsigned long long sendSync (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void slaveMode(void) {
    int fd = context->fd;
    unsigned long long payload = sendSync(fd);
    char buf[1024];
    int original_output = config.output;

    fprintf(stderr,"SYNC with master, discarding %llu "
                   "bytes of bulk transfer...\n", payload);

    /* Discard the payload. */
    while(payload) {
        ssize_t nread;

        nread = read(fd,buf,(payload > sizeof(buf)) ? sizeof(buf) : payload);
        if (nread <= 0) {
            fprintf(stderr,"Error reading RDB payload while SYNCing\n");
            exit(1);
        }
        payload -= nread;
    }
    fprintf(stderr,"SYNC done. Logging commands from master.\n");

    /* Now we can use hidisque to read the incoming protocol. */
    config.output = OUTPUT_CSV;
    while (cliReadReply(0) == REDIS_OK);
    config.output = original_output;
}