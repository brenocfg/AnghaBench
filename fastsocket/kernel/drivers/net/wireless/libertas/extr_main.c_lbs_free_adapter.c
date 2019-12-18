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
struct lbs_private {int /*<<< orphan*/ * networks; int /*<<< orphan*/  command_timer; scalar_t__ event_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBS_DEB_MAIN ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_free (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_free_cmd_buffer (struct lbs_private*) ; 

__attribute__((used)) static void lbs_free_adapter(struct lbs_private *priv)
{
	lbs_deb_enter(LBS_DEB_MAIN);

	lbs_free_cmd_buffer(priv);
	if (priv->event_fifo)
		kfifo_free(priv->event_fifo);
	del_timer(&priv->command_timer);
	kfree(priv->networks);
	priv->networks = NULL;

	lbs_deb_leave(LBS_DEB_MAIN);
}