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
typedef  scalar_t__ UINT64 ;

/* Variables and functions */
 scalar_t__ MAX_LOG_SIZE_DEFAULT ; 
 scalar_t__ logger_max_log_size ; 

void SetMaxLogSize(UINT64 size)
{
	if (size == 0)
	{
		size = MAX_LOG_SIZE_DEFAULT;
	}

	logger_max_log_size = size;
}