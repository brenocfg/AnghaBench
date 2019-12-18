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
struct TYPE_3__ {int stack_ptr; char const* stack; } ;
typedef  TYPE_1__ SRTContext ;

/* Variables and functions */

__attribute__((used)) static int srt_stack_find(SRTContext *s, const char c)
{
    int i;
    for (i = s->stack_ptr-1; i >= 0; i--)
        if (s->stack[i] == c)
            break;
    return i;
}