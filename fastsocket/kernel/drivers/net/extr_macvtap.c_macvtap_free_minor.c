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
struct macvlan_dev {scalar_t__ minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  minor_idr ; 
 int /*<<< orphan*/  minor_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void macvtap_free_minor(struct macvlan_dev *vlan)
{
       mutex_lock(&minor_lock);
       if (vlan->minor) {
               idr_remove(&minor_idr, vlan->minor);
               vlan->minor = 0;
       }
       mutex_unlock(&minor_lock);
}