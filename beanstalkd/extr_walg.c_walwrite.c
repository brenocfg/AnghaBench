#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  nrec; scalar_t__ use; TYPE_6__* cur; } ;
typedef  TYPE_1__ Wal ;
struct TYPE_13__ {scalar_t__ resv; } ;
struct TYPE_12__ {scalar_t__ file; } ;
typedef  TYPE_2__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  filewclose (TYPE_6__*) ; 
 int filewrjobfull (TYPE_6__*,TYPE_2__*) ; 
 int filewrjobshort (TYPE_6__*,TYPE_2__*) ; 
 scalar_t__ usenext (TYPE_1__*) ; 

int
walwrite(Wal *w, Job *j)
{
    int r = 0;

    if (!w->use) return 1;
    if (w->cur->resv > 0 || usenext(w)) {
        if (j->file) {
            r = filewrjobshort(w->cur, j);
        } else {
            r = filewrjobfull(w->cur, j);
        }
    }
    if (!r) {
        filewclose(w->cur);
        w->use = 0;
    }
    w->nrec++;
    return r;
}