#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {void* private_data; } ;
struct agp_file_private {int /*<<< orphan*/  access_flags; int /*<<< orphan*/  my_pid; } ;
struct agp_client {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  agp_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int AGPGART_MINOR ; 
 int /*<<< orphan*/  AGP_FF_ALLOW_CLIENT ; 
 int /*<<< orphan*/  AGP_FF_ALLOW_CONTROLLER ; 
 int /*<<< orphan*/  AGP_FF_IS_CLIENT ; 
 int /*<<< orphan*/  AGP_FF_IS_VALID ; 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int /*<<< orphan*/  DBG (char*,struct agp_file_private*,struct agp_client*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__ agp_fe ; 
 struct agp_client* agp_find_client_by_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_insert_file_private (struct agp_file_private*) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int iminor (struct inode*) ; 
 struct agp_file_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int agp_open(struct inode *inode, struct file *file)
{
	int minor = iminor(inode);
	struct agp_file_private *priv;
	struct agp_client *client;
	int rc = -ENXIO;

	lock_kernel();
	mutex_lock(&(agp_fe.agp_mutex));

	if (minor != AGPGART_MINOR)
		goto err_out;

	priv = kzalloc(sizeof(struct agp_file_private), GFP_KERNEL);
	if (priv == NULL)
		goto err_out_nomem;

	set_bit(AGP_FF_ALLOW_CLIENT, &priv->access_flags);
	priv->my_pid = current->pid;

	if (capable(CAP_SYS_RAWIO)) {
		/* Root priv, can be controller */
		set_bit(AGP_FF_ALLOW_CONTROLLER, &priv->access_flags);
	}
	client = agp_find_client_by_pid(current->pid);

	if (client != NULL) {
		set_bit(AGP_FF_IS_CLIENT, &priv->access_flags);
		set_bit(AGP_FF_IS_VALID, &priv->access_flags);
	}
	file->private_data = (void *) priv;
	agp_insert_file_private(priv);
	DBG("private=%p, client=%p", priv, client);
	mutex_unlock(&(agp_fe.agp_mutex));
	unlock_kernel();
	return 0;

err_out_nomem:
	rc = -ENOMEM;
err_out:
	mutex_unlock(&(agp_fe.agp_mutex));
	unlock_kernel();
	return rc;
}