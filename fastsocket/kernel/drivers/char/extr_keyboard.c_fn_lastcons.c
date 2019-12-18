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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  last_console ; 
 int /*<<< orphan*/  set_console (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fn_lastcons(struct vc_data *vc)
{
	/* switch to the last used console, ChN */
	set_console(last_console);
}