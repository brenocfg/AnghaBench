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
typedef  int u8 ;
struct TYPE_3__ {scalar_t__ bandwidth; } ;
struct TYPE_4__ {TYPE_1__ ofdm; } ;
struct dvb_frontend_parameters {TYPE_2__ u; } ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 scalar_t__ BANDWIDTH_8_MHZ ; 

__attribute__((used)) static void tda665x_bw(struct dvb_frontend *fe, u8 *buf,
		       const struct dvb_frontend_parameters *params)
{
	if (params->u.ofdm.bandwidth == BANDWIDTH_8_MHZ)
		buf[3] |= 0x08;
}