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
 int /*<<< orphan*/  VCOS_LOG_CATEGORY ; 
 int /*<<< orphan*/  mmal_log_level ; 
 int /*<<< orphan*/  vcos_log_register (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_set_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mmal_logging_init(void)
{
   vcos_log_set_level(VCOS_LOG_CATEGORY, mmal_log_level);
   vcos_log_register("mmal", VCOS_LOG_CATEGORY);
}