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
typedef  int /*<<< orphan*/  tSMP_CB ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_RESET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curve_p256_ptr ; 
 int /*<<< orphan*/  curve_ptr ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_cb ; 
 int /*<<< orphan*/  smp_cb_ptr ; 

void SMP_Free(void)
{
    memset(&smp_cb, 0, sizeof(tSMP_CB));
#if SMP_DYNAMIC_MEMORY
    FREE_AND_RESET(smp_cb_ptr);
    FREE_AND_RESET(curve_ptr);
    FREE_AND_RESET(curve_p256_ptr);
#endif /* #if SMP_DYNAMIC_MEMORY */
}