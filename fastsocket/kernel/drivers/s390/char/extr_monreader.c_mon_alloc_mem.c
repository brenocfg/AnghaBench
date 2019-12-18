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
struct mon_private {void** msg_array; } ;
struct mon_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MON_MSGLIM ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mon_free_mem (struct mon_private*) ; 

__attribute__((used)) static struct mon_private *mon_alloc_mem(void)
{
	int i;
	struct mon_private *monpriv;

	monpriv = kzalloc(sizeof(struct mon_private), GFP_KERNEL);
	if (!monpriv)
		return NULL;
	for (i = 0; i < MON_MSGLIM; i++) {
		monpriv->msg_array[i] = kzalloc(sizeof(struct mon_msg),
						    GFP_KERNEL);
		if (!monpriv->msg_array[i]) {
			mon_free_mem(monpriv);
			return NULL;
		}
	}
	return monpriv;
}