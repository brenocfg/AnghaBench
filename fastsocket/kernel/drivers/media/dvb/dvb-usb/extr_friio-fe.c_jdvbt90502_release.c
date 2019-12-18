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
struct jdvbt90502_state {int dummy; } ;
struct dvb_frontend {struct jdvbt90502_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct jdvbt90502_state*) ; 

__attribute__((used)) static void jdvbt90502_release(struct dvb_frontend *fe)
{
	struct jdvbt90502_state *state = fe->demodulator_priv;
	kfree(state);
}