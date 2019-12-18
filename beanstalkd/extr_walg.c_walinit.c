#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tail; int /*<<< orphan*/  cur; } ;
typedef  TYPE_1__ Wal ;
typedef  int /*<<< orphan*/  Job ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  makenextfile (TYPE_1__*) ; 
 int /*<<< orphan*/  twarnx (char*) ; 
 int /*<<< orphan*/  walread (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int walscandir (TYPE_1__*) ; 

void
walinit(Wal *w, Job *list)
{
    int min;

    min = walscandir(w);
    walread(w, list, min);

    // first writable file
    if (!makenextfile(w)) {
        twarnx("makenextfile");
        exit(1);
    }

    w->cur = w->tail;
}