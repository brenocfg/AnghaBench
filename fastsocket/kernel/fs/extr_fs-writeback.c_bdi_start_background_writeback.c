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
struct backing_dev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LONG_MAX ; 
 int /*<<< orphan*/  __bdi_start_writeback (struct backing_dev_info*,int /*<<< orphan*/ ,int,int) ; 

void bdi_start_background_writeback(struct backing_dev_info *bdi)
{
	__bdi_start_writeback(bdi, LONG_MAX, true, true);
}