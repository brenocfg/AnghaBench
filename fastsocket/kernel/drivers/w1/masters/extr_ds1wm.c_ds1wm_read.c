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
struct ds1wm_data {int read_byte; int /*<<< orphan*/ * read_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DS1WM_TIMEOUT ; 
 int /*<<< orphan*/  ds1wm_write (struct ds1wm_data*,unsigned char) ; 
 int /*<<< orphan*/  read_done ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds1wm_read(struct ds1wm_data *ds1wm_data, unsigned char write_data)
{
	DECLARE_COMPLETION_ONSTACK(read_done);
	ds1wm_data->read_complete = &read_done;

	ds1wm_write(ds1wm_data, write_data);
	wait_for_completion_timeout(&read_done, DS1WM_TIMEOUT);
	ds1wm_data->read_complete = NULL;

	return ds1wm_data->read_byte;
}