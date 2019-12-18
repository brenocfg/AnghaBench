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
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_INQ_RESULT_STANDARD ; 
 int /*<<< orphan*/  btm_process_inq_results (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btu_hcif_inquiry_result_evt (UINT8 *p)
{
    /* Store results in the cache */
    btm_process_inq_results (p, BTM_INQ_RESULT_STANDARD);
}