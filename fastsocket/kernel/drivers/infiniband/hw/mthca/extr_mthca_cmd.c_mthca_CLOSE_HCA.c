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
 int /*<<< orphan*/  CMD_CLOSE_HCA ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_C ; 
 int mthca_cmd (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mthca_CLOSE_HCA(struct mthca_dev *dev, int panic)
{
	return mthca_cmd(dev, 0, 0, panic, CMD_CLOSE_HCA, CMD_TIME_CLASS_C);
}