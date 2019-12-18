#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int refs; int /*<<< orphan*/  w; } ;
typedef  TYPE_1__ File ;

/* Variables and functions */
 int /*<<< orphan*/  walgc (int /*<<< orphan*/ ) ; 

void
filedecref(File *f)
{
    if (!f) return;
    f->refs--;
    if (f->refs < 1) {
        walgc(f->w);
    }
}