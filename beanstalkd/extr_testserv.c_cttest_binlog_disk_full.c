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
struct TYPE_3__ {int use; int filesize; int wantsync; scalar_t__ syncrate; int /*<<< orphan*/  dir; } ;
struct TYPE_4__ {TYPE_1__ wal; } ;

/* Variables and functions */
 int SERVER () ; 
 int /*<<< orphan*/  ckresp (int,char*) ; 
 int /*<<< orphan*/  ctdir () ; 
 int /*<<< orphan*/ * falloc ; 
 int* fallocpat ; 
 int mustdiallocal (int) ; 
 int /*<<< orphan*/  mustsend (int,char*) ; 
 int size ; 
 TYPE_2__ srv ; 
 int /*<<< orphan*/  wrapfalloc ; 

void
cttest_binlog_disk_full()
{
    size = 1000;
    falloc = &wrapfalloc;
    fallocpat[0] = 1;
    fallocpat[2] = 1;

    srv.wal.dir = ctdir();
    srv.wal.use = 1;
    srv.wal.filesize = size;
    srv.wal.syncrate = 0;
    srv.wal.wantsync = 1;

    int port = SERVER();
    int fd = mustdiallocal(port);
    mustsend(fd, "put 0 0 100 50\r\n");
    mustsend(fd, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
    ckresp(fd, "INSERTED 1\r\n");
    mustsend(fd, "put 0 0 100 50\r\n");
    mustsend(fd, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
    ckresp(fd, "INSERTED 2\r\n");
    mustsend(fd, "put 0 0 100 50\r\n");
    mustsend(fd, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
    ckresp(fd, "INSERTED 3\r\n");
    mustsend(fd, "put 0 0 100 50\r\n");
    mustsend(fd, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
    ckresp(fd, "INSERTED 4\r\n");

    mustsend(fd, "put 0 0 100 50\r\n");
    mustsend(fd, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
    ckresp(fd, "OUT_OF_MEMORY\r\n");

    mustsend(fd, "put 0 0 100 50\r\n");
    mustsend(fd, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
    ckresp(fd, "INSERTED 6\r\n");
    mustsend(fd, "put 0 0 100 50\r\n");
    mustsend(fd, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
    ckresp(fd, "INSERTED 7\r\n");
    mustsend(fd, "put 0 0 100 50\r\n");
    mustsend(fd, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
    ckresp(fd, "INSERTED 8\r\n");
    mustsend(fd, "put 0 0 100 50\r\n");
    mustsend(fd, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
    ckresp(fd, "INSERTED 9\r\n");

    mustsend(fd, "delete 1\r\n");
    ckresp(fd, "DELETED\r\n");
    mustsend(fd, "delete 2\r\n");
    ckresp(fd, "DELETED\r\n");
    mustsend(fd, "delete 3\r\n");
    ckresp(fd, "DELETED\r\n");
    mustsend(fd, "delete 4\r\n");
    ckresp(fd, "DELETED\r\n");
    mustsend(fd, "delete 6\r\n");
    ckresp(fd, "DELETED\r\n");
    mustsend(fd, "delete 7\r\n");
    ckresp(fd, "DELETED\r\n");
    mustsend(fd, "delete 8\r\n");
    ckresp(fd, "DELETED\r\n");
    mustsend(fd, "delete 9\r\n");
    ckresp(fd, "DELETED\r\n");
}