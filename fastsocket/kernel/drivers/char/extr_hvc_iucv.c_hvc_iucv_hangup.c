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
struct iucv_path {int dummy; } ;
struct hvc_iucv_private {scalar_t__ iucv_state; scalar_t__ tty_state; int /*<<< orphan*/  lock; scalar_t__ is_console; struct iucv_path* path; } ;

/* Variables and functions */
 scalar_t__ IUCV_CONNECTED ; 
 scalar_t__ IUCV_SEVERED ; 
 scalar_t__ TTY_CLOSED ; 
 scalar_t__ TTY_OPENED ; 
 int /*<<< orphan*/  hvc_iucv_cleanup (struct hvc_iucv_private*) ; 
 int /*<<< orphan*/  hvc_kick () ; 
 int /*<<< orphan*/  iucv_path_free (struct iucv_path*) ; 
 int /*<<< orphan*/  iucv_path_sever (struct iucv_path*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hvc_iucv_hangup(struct hvc_iucv_private *priv)
{
	struct iucv_path *path;

	path = NULL;
	spin_lock(&priv->lock);
	if (priv->iucv_state == IUCV_CONNECTED) {
		path = priv->path;
		priv->path = NULL;
		priv->iucv_state = IUCV_SEVERED;
		if (priv->tty_state == TTY_CLOSED)
			hvc_iucv_cleanup(priv);
		else
			/* console is special (see above) */
			if (priv->is_console) {
				hvc_iucv_cleanup(priv);
				priv->tty_state = TTY_OPENED;
			} else
				hvc_kick();
	}
	spin_unlock(&priv->lock);

	/* finally sever path (outside of priv->lock due to lock ordering) */
	if (path) {
		iucv_path_sever(path, NULL);
		iucv_path_free(path);
	}
}