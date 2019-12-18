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
struct mxl5007t_state {int dummy; } ;
struct dvb_frontend {struct mxl5007t_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  hybrid_tuner_release_state (struct mxl5007t_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxl5007t_list_mutex ; 

__attribute__((used)) static int mxl5007t_release(struct dvb_frontend *fe)
{
	struct mxl5007t_state *state = fe->tuner_priv;

	mutex_lock(&mxl5007t_list_mutex);

	if (state)
		hybrid_tuner_release_state(state);

	mutex_unlock(&mxl5007t_list_mutex);

	fe->tuner_priv = NULL;

	return 0;
}