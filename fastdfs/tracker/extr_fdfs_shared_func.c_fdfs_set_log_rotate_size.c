#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {scalar_t__ rotate_size; } ;
typedef  TYPE_1__ LogContext ;

/* Variables and functions */
 int /*<<< orphan*/  log_set_rotate_time_format (TYPE_1__*,char*) ; 

void fdfs_set_log_rotate_size(LogContext *pContext, const int64_t log_rotate_size)
{
	if (log_rotate_size > 0)
	{
		pContext->rotate_size = log_rotate_size;
		log_set_rotate_time_format(pContext, "%Y%m%d_%H%M%S");
	}
	else
	{
		pContext->rotate_size = 0;
		log_set_rotate_time_format(pContext, "%Y%m%d");
	}
}