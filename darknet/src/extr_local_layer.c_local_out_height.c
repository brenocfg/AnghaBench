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
struct TYPE_3__ {int h; int stride; scalar_t__ size; int /*<<< orphan*/  pad; } ;
typedef  TYPE_1__ local_layer ;

/* Variables and functions */

int local_out_height(local_layer l)
{
    int h = l.h;
    if (!l.pad) h -= l.size;
    else h -= 1;
    return h/l.stride + 1;
}