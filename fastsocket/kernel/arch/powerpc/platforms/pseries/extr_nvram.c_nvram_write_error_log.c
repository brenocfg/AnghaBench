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

/* Variables and functions */
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  last_unread_rtas_event ; 
 int nvram_write_os_partition (int /*<<< orphan*/ *,char*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rtas_log_partition ; 

int nvram_write_error_log(char * buff, int length,
                          unsigned int err_type, unsigned int error_log_cnt)
{
	int rc = nvram_write_os_partition(&rtas_log_partition, buff, length,
						err_type, error_log_cnt);
	if (!rc)
		last_unread_rtas_event = get_seconds();
	return rc;
}