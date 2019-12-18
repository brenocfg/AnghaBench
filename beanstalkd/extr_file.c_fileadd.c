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
struct TYPE_6__ {int /*<<< orphan*/  nfile; TYPE_2__* head; TYPE_2__* tail; } ;
typedef  TYPE_1__ Wal ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ File ;

/* Variables and functions */

Wal*
fileadd(File *f, Wal *w)
{
    if (w->tail) {
        w->tail->next = f;
    }
    w->tail = f;
    if (!w->head) {
        w->head = f;
    }
    w->nfile++;
    return w;
}