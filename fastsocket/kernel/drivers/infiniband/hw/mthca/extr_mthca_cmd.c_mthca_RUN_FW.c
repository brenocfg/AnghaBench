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
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RUN_FW ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_A ; 
 int mthca_cmd (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mthca_RUN_FW(struct mthca_dev *dev)
{
	return mthca_cmd(dev, 0, 0, 0, CMD_RUN_FW, CMD_TIME_CLASS_A);
}