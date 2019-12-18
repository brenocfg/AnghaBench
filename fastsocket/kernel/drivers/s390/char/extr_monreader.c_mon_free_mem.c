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
struct mon_private {struct mon_private** msg_array; } ;

/* Variables and functions */
 int MON_MSGLIM ; 
 int /*<<< orphan*/  kfree (struct mon_private*) ; 

__attribute__((used)) static void mon_free_mem(struct mon_private *monpriv)
{
	int i;

	for (i = 0; i < MON_MSGLIM; i++)
		if (monpriv->msg_array[i])
			kfree(monpriv->msg_array[i]);
	kfree(monpriv);
}