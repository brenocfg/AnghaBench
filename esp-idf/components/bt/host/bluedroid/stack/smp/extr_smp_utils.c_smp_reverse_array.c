#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*) ; 

void smp_reverse_array(UINT8 *arr, UINT8 len)
{
    UINT8 i = 0, tmp;

    SMP_TRACE_DEBUG("smp_reverse_array\n");

    for (i = 0; i < len / 2; i ++) {
        tmp = arr[i];
        arr[i] = arr[len - 1 - i];
        arr[len - 1 - i] = tmp;
    }
}