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
typedef  int int64 ;
struct TYPE_3__ {int use; int filesize; int syncrate; int wantsync; int /*<<< orphan*/  dir; } ;
struct TYPE_4__ {TYPE_1__ wal; } ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_DATA_SIZE_LIMIT_MAX ; 
 int SERVER () ; 
 int /*<<< orphan*/  ckresp (int,char*) ; 
 int /*<<< orphan*/  ckrespsub (int,char*) ; 
 int /*<<< orphan*/  ctdir () ; 
 int /*<<< orphan*/  ctresettimer () ; 
 int /*<<< orphan*/  ctsetbytes (int) ; 
 int /*<<< orphan*/  ctstoptimer () ; 
 int /*<<< orphan*/  job_data_size_limit ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int mustdiallocal (int) ; 
 int /*<<< orphan*/  mustsend (int,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_2__ srv ; 

__attribute__((used)) static void
bench_put_delete_size(int n, int size, int walsize, int sync, int64 syncrate_ms)
{
    if (walsize > 0) {
        srv.wal.dir = ctdir();
        srv.wal.use = 1;
        srv.wal.filesize = walsize;
        srv.wal.syncrate = syncrate_ms * 1000000;
        srv.wal.wantsync = sync;
    }

    job_data_size_limit = JOB_DATA_SIZE_LIMIT_MAX;
    int port = SERVER();
    int fd = mustdiallocal(port);
    char buf[50], put[50];
    char body[size+1];
    memset(body, 'a', size);
    body[size] = 0;
    ctsetbytes(size);
    sprintf(put, "put 0 0 0 %d\r\n", size);
    ctresettimer();
    int i;
    for (i = 0; i < n; i++) {
        mustsend(fd, put);
        mustsend(fd, body);
        mustsend(fd, "\r\n");
        ckrespsub(fd, "INSERTED ");
        sprintf(buf, "delete %d\r\n", i + 1);
        mustsend(fd, buf);
        ckresp(fd, "DELETED\r\n");
    }
    ctstoptimer();
}