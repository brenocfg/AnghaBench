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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  markeins_led (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void markeins_led_hex(u32 val)
{
	char str[10];

	sprintf(str, "%08x", val);
	markeins_led(str);
}