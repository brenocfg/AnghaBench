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
struct sdebug_dev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  INVALID_FIELD_IN_CDB ; 
 int check_condition_result ; 
 int /*<<< orphan*/  mk_sense_buffer (struct sdebug_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long long sdebug_capacity ; 
 unsigned int sdebug_store_sectors ; 

__attribute__((used)) static int check_device_access_params(struct sdebug_dev_info *devi,
				      unsigned long long lba, unsigned int num)
{
	if (lba + num > sdebug_capacity) {
		mk_sense_buffer(devi, ILLEGAL_REQUEST, ADDR_OUT_OF_RANGE, 0);
		return check_condition_result;
	}
	/* transfer length excessive (tie in to block limits VPD page) */
	if (num > sdebug_store_sectors) {
		mk_sense_buffer(devi, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB, 0);
		return check_condition_result;
	}
	return 0;
}