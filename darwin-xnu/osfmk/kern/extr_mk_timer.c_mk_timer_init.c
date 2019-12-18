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
typedef  int /*<<< orphan*/  mk_timer_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Z_NOENCRYPT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * mk_timer_zone ; 
 int /*<<< orphan*/ * zinit (int,int,int,char*) ; 
 int /*<<< orphan*/  zone_change (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mk_timer_init(void)
{
	int			s = sizeof (mk_timer_data_t);

	assert(!(mk_timer_zone != NULL));

	mk_timer_zone = zinit(s, (4096 * s), (16 * s), "mk_timer");

	zone_change(mk_timer_zone, Z_NOENCRYPT, TRUE);
}