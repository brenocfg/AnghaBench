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
struct tuner_simple_priv {int dummy; } ;
struct dvb_frontend {struct tuner_simple_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  hybrid_tuner_release_state (struct tuner_simple_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuner_simple_list_mutex ; 

__attribute__((used)) static int simple_release(struct dvb_frontend *fe)
{
	struct tuner_simple_priv *priv = fe->tuner_priv;

	mutex_lock(&tuner_simple_list_mutex);

	if (priv)
		hybrid_tuner_release_state(priv);

	mutex_unlock(&tuner_simple_list_mutex);

	fe->tuner_priv = NULL;

	return 0;
}