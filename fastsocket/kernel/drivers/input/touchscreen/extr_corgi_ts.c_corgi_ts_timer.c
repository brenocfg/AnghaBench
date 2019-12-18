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
struct corgi_ts {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ts_interrupt_main (struct corgi_ts*,int) ; 

__attribute__((used)) static void corgi_ts_timer(unsigned long data)
{
	struct corgi_ts *corgits_data = (struct corgi_ts *) data;

	ts_interrupt_main(corgits_data, 1);
}