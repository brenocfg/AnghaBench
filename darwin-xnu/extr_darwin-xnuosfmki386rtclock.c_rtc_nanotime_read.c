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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  _rtc_nanotime_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pal_rtc_nanotime_info ; 

__attribute__((used)) static inline uint64_t
rtc_nanotime_read(void)
{
	return	_rtc_nanotime_read(&pal_rtc_nanotime_info);
}