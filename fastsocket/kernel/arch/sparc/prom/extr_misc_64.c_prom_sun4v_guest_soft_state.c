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
 int /*<<< orphan*/  P1275_INOUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p1275_cmd (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prom_service_exists (char const*) ; 

void prom_sun4v_guest_soft_state(void)
{
	const char *svc = "SUNW,soft-state-supported";

	if (!prom_service_exists(svc))
		return;
	p1275_cmd(svc, P1275_INOUT(0, 0));
}