#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCOS_LOG_CAT_T ;
struct TYPE_2__ {int /*<<< orphan*/ * log_category; } ;

/* Variables and functions */
 TYPE_1__ cmd_globals ; 

void vcos_cmd_always_log_output( VCOS_LOG_CAT_T *log_category )
{
    cmd_globals.log_category = log_category;
}