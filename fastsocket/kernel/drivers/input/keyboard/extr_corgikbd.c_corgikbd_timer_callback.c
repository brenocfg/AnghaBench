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
struct corgikbd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  corgikbd_scankeyboard (struct corgikbd*) ; 

__attribute__((used)) static void corgikbd_timer_callback(unsigned long data)
{
	struct corgikbd *corgikbd_data = (struct corgikbd *) data;
	corgikbd_scankeyboard(corgikbd_data);
}