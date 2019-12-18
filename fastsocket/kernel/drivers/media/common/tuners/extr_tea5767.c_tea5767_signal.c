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
struct tea5767_priv {int dummy; } ;
struct dvb_frontend {struct tea5767_priv* tuner_priv; } ;

/* Variables and functions */
 char const TEA5767_ADC_LEVEL_MASK ; 
 int /*<<< orphan*/  tuner_dbg (char*,int) ; 

__attribute__((used)) static inline int tea5767_signal(struct dvb_frontend *fe, const char *buffer)
{
	struct tea5767_priv *priv = fe->tuner_priv;

	int signal = ((buffer[3] & TEA5767_ADC_LEVEL_MASK) << 8);

	tuner_dbg("Signal strength: %d\n", signal);

	return signal;
}