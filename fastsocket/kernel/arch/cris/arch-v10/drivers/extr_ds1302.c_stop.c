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
 int /*<<< orphan*/  TK_RST_OUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tempudelay (int) ; 

__attribute__((used)) static void
stop(void) 
{
	tempudelay(2);
	TK_RST_OUT(0);
}