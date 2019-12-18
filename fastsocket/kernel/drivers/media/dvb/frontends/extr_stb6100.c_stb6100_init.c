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
struct tuner_state {int tunerstep; int refclock; int iqsense; int bandwidth; scalar_t__ ifreq; } ;
struct stb6100_state {int bandwidth; int reference; struct tuner_state status; } ;
struct dvb_frontend {struct stb6100_state* tuner_priv; } ;

/* Variables and functions */

__attribute__((used)) static int stb6100_init(struct dvb_frontend *fe)
{
	struct stb6100_state *state = fe->tuner_priv;
	struct tuner_state *status = &state->status;

	status->tunerstep	= 125000;
	status->ifreq		= 0;
	status->refclock	= 27000000;	/* Hz	*/
	status->iqsense		= 1;
	status->bandwidth	= 36000;	/* kHz	*/
	state->bandwidth	= status->bandwidth * 1000;	/* Hz	*/
	state->reference	= status->refclock / 1000;	/* kHz	*/

	/* Set default bandwidth. Modified, PN 13-May-10	*/
	return 0;
}