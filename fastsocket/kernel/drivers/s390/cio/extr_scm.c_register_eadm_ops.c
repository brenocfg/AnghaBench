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
struct eadm_ops {int dummy; } ;

/* Variables and functions */
 struct eadm_ops* eadm_ops ; 
 int /*<<< orphan*/  eadm_ops_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void register_eadm_ops(struct eadm_ops *ops)
{
	mutex_lock(&eadm_ops_mutex);
	eadm_ops = ops;
	mutex_unlock(&eadm_ops_mutex);
}