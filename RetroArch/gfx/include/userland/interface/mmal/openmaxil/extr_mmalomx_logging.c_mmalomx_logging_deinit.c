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
struct TYPE_2__ {int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_LOG_CATEGORY ; 
 TYPE_1__ mmalomx_log_category ; 
 int /*<<< orphan*/  mmalomx_log_level ; 
 int /*<<< orphan*/  vcos_log_unregister (int /*<<< orphan*/ ) ; 

void mmalomx_logging_deinit(void)
{
   mmalomx_log_level = mmalomx_log_category.level;
   vcos_log_unregister(VCOS_LOG_CATEGORY);
}