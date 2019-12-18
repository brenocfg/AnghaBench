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
struct st5481_bcs {int /*<<< orphan*/  b_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*) ; 
 int /*<<< orphan*/  st5481_release_b_out (struct st5481_bcs*) ; 
 int /*<<< orphan*/  st5481_release_in (int /*<<< orphan*/ *) ; 

void st5481_release_b(struct st5481_bcs *bcs)
{
	DBG(4,"");

	st5481_release_in(&bcs->b_in);
	st5481_release_b_out(bcs);
}