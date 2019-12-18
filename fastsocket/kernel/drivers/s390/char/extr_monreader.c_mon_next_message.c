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
struct mon_private {size_t read_index; int /*<<< orphan*/  read_ready; struct mon_msg** msg_array; } ;
struct mon_msg {scalar_t__ mca_offset; scalar_t__ pos; scalar_t__ msglim_reached; scalar_t__ replied_msglim; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 struct mon_msg* ERR_PTR (int /*<<< orphan*/ ) ; 
 int MON_MSGLIM ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static struct mon_msg *mon_next_message(struct mon_private *monpriv)
{
	struct mon_msg *monmsg;

	if (!atomic_read(&monpriv->read_ready))
		return NULL;
	monmsg = monpriv->msg_array[monpriv->read_index];
	if (unlikely(monmsg->replied_msglim)) {
		monmsg->replied_msglim = 0;
		monmsg->msglim_reached = 0;
		monmsg->pos = 0;
		monmsg->mca_offset = 0;
		monpriv->read_index = (monpriv->read_index + 1) %
				      MON_MSGLIM;
		atomic_dec(&monpriv->read_ready);
		return ERR_PTR(-EOVERFLOW);
	}
	return monmsg;
}