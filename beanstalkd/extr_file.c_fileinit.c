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
struct TYPE_5__ {int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__ Wal ;
struct TYPE_6__ {int seq; int /*<<< orphan*/  path; TYPE_1__* w; } ;
typedef  TYPE_2__ File ;

/* Variables and functions */
 int /*<<< orphan*/  fmtalloc (char*,int /*<<< orphan*/ ,int) ; 

int
fileinit(File *f, Wal *w, int n)
{
    f->w = w;
    f->seq = n;
    f->path = fmtalloc("%s/binlog.%d", w->dir, n);
    return !!f->path;
}