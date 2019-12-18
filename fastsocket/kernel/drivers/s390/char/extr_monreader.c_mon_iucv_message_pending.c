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
struct mon_private {size_t write_index; int /*<<< orphan*/  read_ready; TYPE_1__** msg_array; int /*<<< orphan*/  msglim_count; } ;
struct iucv_path {struct mon_private* private; } ;
struct iucv_message {int dummy; } ;
struct TYPE_2__ {int msglim_reached; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int MON_MSGLIM ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct iucv_message*,int) ; 
 int /*<<< orphan*/  mon_read_wait_queue ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mon_iucv_message_pending(struct iucv_path *path,
				     struct iucv_message *msg)
{
	struct mon_private *monpriv = path->private;

	memcpy(&monpriv->msg_array[monpriv->write_index]->msg,
	       msg, sizeof(*msg));
	if (atomic_inc_return(&monpriv->msglim_count) == MON_MSGLIM) {
		pr_warning("The read queue for monitor data is full\n");
		monpriv->msg_array[monpriv->write_index]->msglim_reached = 1;
	}
	monpriv->write_index = (monpriv->write_index + 1) % MON_MSGLIM;
	atomic_inc(&monpriv->read_ready);
	wake_up_interruptible(&mon_read_wait_queue);
}