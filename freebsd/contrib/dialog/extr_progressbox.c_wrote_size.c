#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* link; } ;
typedef  TYPE_1__ WROTE ;
struct TYPE_5__ {TYPE_1__* wrote; } ;
typedef  TYPE_2__ MY_OBJ ;

/* Variables and functions */

__attribute__((used)) static int
wrote_size(MY_OBJ * obj, int want)
{
    int result = 0;
    WROTE *wrote = obj->wrote;
    while (wrote != NULL && want > 0) {
	wrote = wrote->link;
	want--;
	result++;
    }
    return result;
}