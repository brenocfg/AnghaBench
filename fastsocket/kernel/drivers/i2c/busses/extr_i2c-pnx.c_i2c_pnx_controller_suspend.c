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
struct platform_device {int dummy; } ;
struct i2c_pnx_data {int (* suspend ) (struct platform_device*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 struct i2c_pnx_data* platform_get_drvdata (struct platform_device*) ; 
 int stub1 (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_pnx_controller_suspend(struct platform_device *pdev,
				      pm_message_t state)
{
	struct i2c_pnx_data *i2c_pnx = platform_get_drvdata(pdev);
	return i2c_pnx->suspend(pdev, state);
}