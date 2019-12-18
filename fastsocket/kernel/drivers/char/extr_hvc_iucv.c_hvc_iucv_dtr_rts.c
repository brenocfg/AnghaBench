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
struct hvc_struct {int /*<<< orphan*/  vtermno; } ;
struct hvc_iucv_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  iucv_state; struct iucv_path* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  IUCV_DISCONN ; 
 int /*<<< orphan*/  flush_sndbuf_sync (struct hvc_iucv_private*) ; 
 struct hvc_iucv_private* hvc_iucv_get_private (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_path_free (struct iucv_path*) ; 
 int /*<<< orphan*/  iucv_path_sever (struct iucv_path*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hvc_iucv_dtr_rts(struct hvc_struct *hp, int raise)
{
	struct hvc_iucv_private *priv;
	struct iucv_path        *path;

	/* Raising the DTR/RTS is ignored as IUCV connections can be
	 * established at any times.
	 */
	if (raise)
		return;

	priv = hvc_iucv_get_private(hp->vtermno);
	if (!priv)
		return;

	/* Lowering the DTR/RTS lines disconnects an established IUCV
	 * connection.
	 */
	flush_sndbuf_sync(priv);

	spin_lock_bh(&priv->lock);
	path = priv->path;		/* save reference to IUCV path */
	priv->path = NULL;
	priv->iucv_state = IUCV_DISCONN;
	spin_unlock_bh(&priv->lock);

	/* Sever IUCV path outside of priv->lock due to lock ordering of:
	 * priv->lock <--> iucv_table_lock */
	if (path) {
		iucv_path_sever(path, NULL);
		iucv_path_free(path);
	}
}