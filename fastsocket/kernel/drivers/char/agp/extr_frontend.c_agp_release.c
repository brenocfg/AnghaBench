#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {struct agp_file_private* private_data; } ;
struct agp_file_private {int /*<<< orphan*/  my_pid; int /*<<< orphan*/  access_flags; } ;
struct agp_controller {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  agp_mutex; struct agp_controller* current_controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_FF_IS_CLIENT ; 
 int /*<<< orphan*/  AGP_FF_IS_CONTROLLER ; 
 int /*<<< orphan*/  DBG (char*,struct agp_file_private*) ; 
 int /*<<< orphan*/  agp_controller_release_current (struct agp_controller*,struct agp_file_private*) ; 
 TYPE_1__ agp_fe ; 
 struct agp_controller* agp_find_controller_by_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_remove_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_remove_controller (struct agp_controller*) ; 
 int /*<<< orphan*/  agp_remove_file_private (struct agp_file_private*) ; 
 int /*<<< orphan*/  kfree (struct agp_file_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int agp_release(struct inode *inode, struct file *file)
{
	struct agp_file_private *priv = file->private_data;

	mutex_lock(&(agp_fe.agp_mutex));

	DBG("priv=%p", priv);

	if (test_bit(AGP_FF_IS_CONTROLLER, &priv->access_flags)) {
		struct agp_controller *controller;

		controller = agp_find_controller_by_pid(priv->my_pid);

		if (controller != NULL) {
			if (controller == agp_fe.current_controller)
				agp_controller_release_current(controller, priv);
			agp_remove_controller(controller);
			controller = NULL;
		}
	}

	if (test_bit(AGP_FF_IS_CLIENT, &priv->access_flags))
		agp_remove_client(priv->my_pid);

	agp_remove_file_private(priv);
	kfree(priv);
	file->private_data = NULL;
	mutex_unlock(&(agp_fe.agp_mutex));
	return 0;
}