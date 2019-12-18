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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int cx24116_read_snr_esno (struct dvb_frontend*,int /*<<< orphan*/ *) ; 
 int cx24116_read_snr_pct (struct dvb_frontend*,int /*<<< orphan*/ *) ; 
 int esno_snr ; 

__attribute__((used)) static int cx24116_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	if (esno_snr == 1)
		return cx24116_read_snr_esno(fe, snr);
	else
		return cx24116_read_snr_pct(fe, snr);
}