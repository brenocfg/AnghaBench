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
struct locomokbd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  locomokbd_scankeyboard (struct locomokbd*) ; 

__attribute__((used)) static void locomokbd_timer_callback(unsigned long data)
{
	struct locomokbd *locomokbd = (struct locomokbd *) data;

	locomokbd_scankeyboard(locomokbd);
}