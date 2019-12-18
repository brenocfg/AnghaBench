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
typedef  int uint8_t ;
typedef  enum ds1511reg { ____Placeholder_ds1511reg } ds1511reg ;

/* Variables and functions */
 int /*<<< orphan*/  rtc_write (int,int) ; 

__attribute__((used)) static inline void
rtc_write_alarm(uint8_t val, enum ds1511reg reg)
{
	rtc_write((val | 0x80), reg);
}