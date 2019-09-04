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
struct TYPE_3__ {size_t* seen; size_t batch; size_t subdivisions; } ;
typedef  TYPE_1__ network ;

/* Variables and functions */

size_t get_current_batch(network *net)
{
    size_t batch_num = (*net->seen)/(net->batch*net->subdivisions);
    return batch_num;
}