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
typedef  int /*<<< orphan*/  u8 ;
struct ds1wm_data {int /*<<< orphan*/ * write_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DS1WM_DATA ; 
 int /*<<< orphan*/  DS1WM_TIMEOUT ; 
 int /*<<< orphan*/  ds1wm_write_register (struct ds1wm_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_done ; 

__attribute__((used)) static int ds1wm_write(struct ds1wm_data *ds1wm_data, u8 data)
{
	DECLARE_COMPLETION_ONSTACK(write_done);
	ds1wm_data->write_complete = &write_done;

	ds1wm_write_register(ds1wm_data, DS1WM_DATA, data);

	wait_for_completion_timeout(&write_done, DS1WM_TIMEOUT);
	ds1wm_data->write_complete = NULL;

	return 0;
}