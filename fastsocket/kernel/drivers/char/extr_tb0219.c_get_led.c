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
 int /*<<< orphan*/  TB0219_LED ; 
 scalar_t__ tb0219_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char get_led(void)
{
	return (char)tb0219_read(TB0219_LED);
}