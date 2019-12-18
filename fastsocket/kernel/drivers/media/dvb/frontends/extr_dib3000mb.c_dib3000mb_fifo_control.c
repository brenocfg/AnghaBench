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
struct dvb_frontend {struct dib3000_state* demodulator_priv; } ;
struct dib3000_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIB3000MB_FIFO_ACTIVATE ; 
 int /*<<< orphan*/  DIB3000MB_FIFO_INHIBIT ; 
 int /*<<< orphan*/  DIB3000MB_REG_FIFO ; 
 int /*<<< orphan*/  deb_xfer (char*,char*) ; 
 int /*<<< orphan*/  wr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib3000mb_fifo_control(struct dvb_frontend *fe, int onoff)
{
	struct dib3000_state *state = fe->demodulator_priv;

	deb_xfer("%s fifo\n",onoff ? "enabling" : "disabling");
	if (onoff) {
		wr(DIB3000MB_REG_FIFO, DIB3000MB_FIFO_ACTIVATE);
	} else {
		wr(DIB3000MB_REG_FIFO, DIB3000MB_FIFO_INHIBIT);
	}
	return 0;
}