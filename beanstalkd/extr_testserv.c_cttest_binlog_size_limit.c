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
struct TYPE_3__ {int dir; int use; int filesize; int wantsync; scalar_t__ syncrate; } ;
struct TYPE_4__ {TYPE_1__ wal; } ;

/* Variables and functions */
 int SERVER () ; 
 int /*<<< orphan*/  assertf (int,char*,int,int) ; 
 int /*<<< orphan*/  ckresp (int,char*) ; 
 int ctdir () ; 
 int /*<<< orphan*/  exist (char*) ; 
 int filesize (char*) ; 
 char* fmtalloc (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int mustdiallocal (int) ; 
 int /*<<< orphan*/  mustsend (int,char*) ; 
 int size ; 
 TYPE_2__ srv ; 

void
cttest_binlog_size_limit()
{
    int i = 0;
    int gotsize;

    size = 4096;
    srv.wal.dir = ctdir();
    srv.wal.use = 1;
    srv.wal.filesize = size;
    srv.wal.syncrate = 0;
    srv.wal.wantsync = 1;

    int port = SERVER();
    int fd = mustdiallocal(port);
    char *b2 = fmtalloc("%s/binlog.2", ctdir());
    while (!exist(b2)) {
        char *exp = fmtalloc("INSERTED %d\r\n", ++i);
        mustsend(fd, "put 0 0 100 50\r\n");
        mustsend(fd, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
        ckresp(fd, exp);
        free(exp);
    }

    char *b1 = fmtalloc("%s/binlog.1", ctdir());
    gotsize = filesize(b1);
    assertf(gotsize == size, "binlog.1 %d != %d", gotsize, size);
    gotsize = filesize(b2);
    assertf(gotsize == size, "binlog.2 %d != %d", gotsize, size);
    free(b1);
    free(b2);
}