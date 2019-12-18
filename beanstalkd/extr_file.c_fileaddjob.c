#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* fprev; struct TYPE_6__* fnext; TYPE_2__* file; } ;
struct TYPE_7__ {TYPE_1__ jlist; } ;
typedef  TYPE_1__ Job ;
typedef  TYPE_2__ File ;

/* Variables and functions */
 int /*<<< orphan*/  fileincref (TYPE_2__*) ; 

void
fileaddjob(File *f, Job *j)
{
    Job *h;

    h = &f->jlist;
    if (!h->fprev) h->fprev = h;
    j->file = f;
    j->fprev = h->fprev;
    j->fnext = h;
    h->fprev->fnext = j;
    h->fprev = j;
    fileincref(f);
}