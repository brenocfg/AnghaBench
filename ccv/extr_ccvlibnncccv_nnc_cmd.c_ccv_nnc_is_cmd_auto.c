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
typedef  int /*<<< orphan*/  ccv_nnc_cmd_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_nnc_cmd_auto ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

int ccv_nnc_is_cmd_auto(const ccv_nnc_cmd_param_t params)
{
	return (memcmp(&params, &ccv_nnc_cmd_auto, sizeof(ccv_nnc_cmd_param_t)) == 0);
}