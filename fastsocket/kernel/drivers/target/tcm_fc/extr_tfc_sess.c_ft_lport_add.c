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
struct fc_lport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ft_lport_lock ; 
 int /*<<< orphan*/  ft_tport_create (struct fc_lport*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ft_lport_add(struct fc_lport *lport, void *arg)
{
	mutex_lock(&ft_lport_lock);
	ft_tport_create(lport);
	mutex_unlock(&ft_lport_lock);
}