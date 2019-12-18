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
typedef  int /*<<< orphan*/  mfxFrameSurface1 ;
struct TYPE_6__ {TYPE_1__* work_frames; } ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  surface; } ;
typedef  TYPE_1__ QSVFrame ;
typedef  TYPE_2__ QSVContext ;

/* Variables and functions */

__attribute__((used)) static QSVFrame *find_frame(QSVContext *q, mfxFrameSurface1 *surf)
{
    QSVFrame *cur = q->work_frames;
    while (cur) {
        if (surf == &cur->surface)
            return cur;
        cur = cur->next;
    }
    return NULL;
}