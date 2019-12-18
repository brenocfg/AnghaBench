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
struct TYPE_6__ {TYPE_1__* plane; scalar_t__ should_free_lines; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tmp; int /*<<< orphan*/  line; } ;
typedef  TYPE_2__ SwsSlice ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_lines (TYPE_2__*) ; 

__attribute__((used)) static void free_slice(SwsSlice *s)
{
    int i;
    if (s) {
        if (s->should_free_lines)
            free_lines(s);
        for (i = 0; i < 4; ++i) {
            av_freep(&s->plane[i].line);
            s->plane[i].tmp = NULL;
        }
    }
}