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
struct va1j5jf8007s_state {int tune_state; } ;
struct dvb_frontend {struct va1j5jf8007s_state* demodulator_priv; } ;
typedef  int fe_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
#define  VA1J5JF8007S_CHECK_FREQUENCY 137 
#define  VA1J5JF8007S_CHECK_MODULATION 136 
#define  VA1J5JF8007S_CHECK_TS_ID 135 
#define  VA1J5JF8007S_IDLE 134 
#define  VA1J5JF8007S_SET_FREQUENCY_1 133 
#define  VA1J5JF8007S_SET_FREQUENCY_2 132 
#define  VA1J5JF8007S_SET_FREQUENCY_3 131 
#define  VA1J5JF8007S_SET_MODULATION 130 
#define  VA1J5JF8007S_SET_TS_ID 129 
#define  VA1J5JF8007S_TRACK 128 

__attribute__((used)) static int
va1j5jf8007s_read_status(struct dvb_frontend *fe, fe_status_t *status)
{
	struct va1j5jf8007s_state *state;

	state = fe->demodulator_priv;

	switch (state->tune_state) {
	case VA1J5JF8007S_IDLE:
	case VA1J5JF8007S_SET_FREQUENCY_1:
	case VA1J5JF8007S_SET_FREQUENCY_2:
	case VA1J5JF8007S_SET_FREQUENCY_3:
	case VA1J5JF8007S_CHECK_FREQUENCY:
		*status = 0;
		return 0;


	case VA1J5JF8007S_SET_MODULATION:
	case VA1J5JF8007S_CHECK_MODULATION:
		*status |= FE_HAS_SIGNAL;
		return 0;

	case VA1J5JF8007S_SET_TS_ID:
	case VA1J5JF8007S_CHECK_TS_ID:
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER;
		return 0;

	case VA1J5JF8007S_TRACK:
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_LOCK;
		return 0;
	}

	BUG();
}