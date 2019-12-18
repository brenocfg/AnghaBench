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
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON_NOT_POWER_OF_2 (int) ; 
 int SCI_MAX_IO_REQUESTS ; 
 int SCI_MAX_SEQ ; 
 int SCU_ABSOLUTE_MAX_UNSOLICITED_FRAMES ; 
 int SCU_MAX_COMPLETION_QUEUE_ENTRIES ; 
 int SCU_MAX_EVENTS ; 
 int SCU_MAX_UNSOLICITED_FRAMES ; 

__attribute__((used)) static inline void check_sizes(void)
{
	BUILD_BUG_ON_NOT_POWER_OF_2(SCU_MAX_EVENTS);
	BUILD_BUG_ON(SCU_MAX_UNSOLICITED_FRAMES <= 8);
	BUILD_BUG_ON_NOT_POWER_OF_2(SCU_MAX_UNSOLICITED_FRAMES);
	BUILD_BUG_ON_NOT_POWER_OF_2(SCU_MAX_COMPLETION_QUEUE_ENTRIES);
	BUILD_BUG_ON(SCU_MAX_UNSOLICITED_FRAMES > SCU_ABSOLUTE_MAX_UNSOLICITED_FRAMES);
	BUILD_BUG_ON_NOT_POWER_OF_2(SCI_MAX_IO_REQUESTS);
	BUILD_BUG_ON_NOT_POWER_OF_2(SCI_MAX_SEQ);
}