#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int test_size; int /*<<< orphan*/ * freq_list; } ;
typedef  TYPE_1__ spitest_param_set_t ;

/* Variables and functions */
 int /*<<< orphan*/ * test_freq_default ; 

void spitest_def_param(void* arg)
{
    spitest_param_set_t *param_set=(spitest_param_set_t*)arg;
    param_set->test_size = 8;
    if (param_set->freq_list==NULL) param_set->freq_list = test_freq_default;
}