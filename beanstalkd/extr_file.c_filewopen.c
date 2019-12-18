#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fd; int iswopen; scalar_t__ resv; TYPE_1__* w; scalar_t__ free; int /*<<< orphan*/  path; } ;
struct TYPE_5__ {scalar_t__ filesize; } ;
typedef  TYPE_2__ File ;

/* Variables and functions */
 int O_CREAT ; 
 int O_WRONLY ; 
 int Walver ; 
 int close (int) ; 
 int errno ; 
 int falloc (int,scalar_t__) ; 
 int /*<<< orphan*/  fileincref (TYPE_2__*) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  twarn (char*,...) ; 
 int unlink (int /*<<< orphan*/ ) ; 
 int write (int,int*,int) ; 

void
filewopen(File *f)
{
    int fd, r;
    int n;
    int ver = Walver;

    fd = open(f->path, O_WRONLY|O_CREAT, 0400);
    if (fd < 0) {
        twarn("open %s", f->path);
        return;
    }

    r = falloc(fd, f->w->filesize);
    if (r) {
        if (close(fd) == -1)
            twarn("close");
        errno = r;
        twarn("falloc %s", f->path);
        r = unlink(f->path);
        if (r) {
            twarn("unlink %s", f->path);
        }
        return;
    }

    n = write(fd, &ver, sizeof(int));
    if (n < 0 || (size_t)n < sizeof(int)) {
        twarn("write %s", f->path);
        if (close(fd) == -1)
            twarn("close");
        return;
    }

    f->fd = fd;
    f->iswopen = 1;
    fileincref(f);
    f->free = f->w->filesize - n;
    f->resv = 0;
}