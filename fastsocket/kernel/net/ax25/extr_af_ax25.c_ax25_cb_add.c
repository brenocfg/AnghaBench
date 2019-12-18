#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ax25_node; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
 int /*<<< orphan*/  ax25_cb_hold (TYPE_1__*) ; 
 int /*<<< orphan*/  ax25_list ; 
 int /*<<< orphan*/  ax25_list_lock ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ax25_cb_add(ax25_cb *ax25)
{
	spin_lock_bh(&ax25_list_lock);
	ax25_cb_hold(ax25);
	hlist_add_head(&ax25->ax25_node, &ax25_list);
	spin_unlock_bh(&ax25_list_lock);
}