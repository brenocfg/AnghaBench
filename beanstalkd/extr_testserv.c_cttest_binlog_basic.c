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
struct TYPE_3__ {int use; int /*<<< orphan*/  dir; } ;
struct TYPE_4__ {TYPE_1__ wal; } ;

/* Variables and functions */
 int SERVER () ; 
 int /*<<< orphan*/  ckresp (int,char*) ; 
 int /*<<< orphan*/  ctdir () ; 
 int job_data_size_limit ; 
 int /*<<< orphan*/  kill_srvpid () ; 
 int mustdiallocal (int) ; 
 int /*<<< orphan*/  mustsend (int,char*) ; 
 TYPE_2__ srv ; 

void
cttest_binlog_basic()
{
    srv.wal.dir = ctdir();
    srv.wal.use = 1;
    job_data_size_limit = 10;

    int port = SERVER();
    int fd = mustdiallocal(port);
    mustsend(fd, "put 0 0 100 0\r\n");
    mustsend(fd, "\r\n");
    ckresp(fd, "INSERTED 1\r\n");

    kill_srvpid();

    port = SERVER();
    fd = mustdiallocal(port);
    mustsend(fd, "delete 1\r\n");
    ckresp(fd, "DELETED\r\n");
}