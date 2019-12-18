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
struct hw {scalar_t__ model; } ;
struct adc_conf {int /*<<< orphan*/  mic20db; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 scalar_t__ CTSB055X ; 
 int adc_init_SB055x (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int adc_init_SBx (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_adc_init(struct hw *hw, const struct adc_conf *info)
{
	if (hw->model == CTSB055X)
		return adc_init_SB055x(hw, info->input, info->mic20db);
	else
		return adc_init_SBx(hw, info->input, info->mic20db);
}