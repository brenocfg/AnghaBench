#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dvb_frontend_parameters {int dummy; } ;
struct TYPE_2__ {int bandwidth_hz; scalar_t__ isdbt_partial_reception; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; } ;
struct dvb_frontend {TYPE_1__ dtv_property_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUARD_INTERVAL_AUTO ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_AUTO ; 

__attribute__((used)) static int mb86a20s_get_frontend(struct dvb_frontend *fe,
	struct dvb_frontend_parameters *p)
{

	/* FIXME: For now, it does nothing */

	fe->dtv_property_cache.bandwidth_hz = 6000000;
	fe->dtv_property_cache.transmission_mode = TRANSMISSION_MODE_AUTO;
	fe->dtv_property_cache.guard_interval = GUARD_INTERVAL_AUTO;
	fe->dtv_property_cache.isdbt_partial_reception = 0;

	return 0;
}