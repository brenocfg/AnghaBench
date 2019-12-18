#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hierarchy_information; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  constellation; void* code_rate_LP; void* code_rate_HP; int /*<<< orphan*/  bandwidth; } ;
struct TYPE_3__ {TYPE_2__ ofdm; } ;
struct dvb_frontend_parameters {TYPE_1__ u; int /*<<< orphan*/  inversion; } ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_6_MHZ ; 
 void* FEC_AUTO ; 
 int /*<<< orphan*/  GUARD_INTERVAL_AUTO ; 
 int /*<<< orphan*/  HIERARCHY_AUTO ; 
 int /*<<< orphan*/  INVERSION_AUTO ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_AUTO ; 

__attribute__((used)) static int jdvbt90502_get_frontend(struct dvb_frontend *fe,
				   struct dvb_frontend_parameters *p)
{
	p->inversion = INVERSION_AUTO;
	p->u.ofdm.bandwidth = BANDWIDTH_6_MHZ;
	p->u.ofdm.code_rate_HP = FEC_AUTO;
	p->u.ofdm.code_rate_LP = FEC_AUTO;
	p->u.ofdm.constellation = QAM_64;
	p->u.ofdm.transmission_mode = TRANSMISSION_MODE_AUTO;
	p->u.ofdm.guard_interval = GUARD_INTERVAL_AUTO;
	p->u.ofdm.hierarchy_information = HIERARCHY_AUTO;
	return 0;
}