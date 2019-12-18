#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  TYPE_1__* host_priv_t ;
struct TYPE_5__ {int /*<<< orphan*/ * special; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  host_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  host_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  is_valid_host_special_port (int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

kern_return_t
kernel_get_special_port(host_priv_t host_priv, int id, ipc_port_t * portp)
{
	if (!is_valid_host_special_port(id))
		panic("attempted to get invalid special port %d", id);

	host_lock(host_priv);
	*portp = host_priv->special[id];
	host_unlock(host_priv);
	return (KERN_SUCCESS);
}