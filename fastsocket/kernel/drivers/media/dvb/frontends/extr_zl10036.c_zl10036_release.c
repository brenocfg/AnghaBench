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
struct zl10036_state {int dummy; } ;
struct dvb_frontend {struct zl10036_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct zl10036_state*) ; 

__attribute__((used)) static int zl10036_release(struct dvb_frontend *fe)
{
	struct zl10036_state *state = fe->tuner_priv;

	fe->tuner_priv = NULL;
	kfree(state);

	return 0;
}