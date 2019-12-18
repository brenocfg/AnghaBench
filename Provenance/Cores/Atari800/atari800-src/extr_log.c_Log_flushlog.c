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
 scalar_t__* Log_buffer ; 
 int /*<<< orphan*/  PRINT (scalar_t__*) ; 

void Log_flushlog(void)
{
#ifdef BUFFERED_LOG
	if (*Log_buffer) {
		PRINT(Log_buffer);
		*Log_buffer = 0;
	}
#endif
}