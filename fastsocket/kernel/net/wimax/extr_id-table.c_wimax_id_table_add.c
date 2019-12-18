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
struct wimax_dev {int /*<<< orphan*/  id_table_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_fnend (int,int /*<<< orphan*/ *,char*,struct wimax_dev*) ; 
 int /*<<< orphan*/  d_fnstart (int,int /*<<< orphan*/ *,char*,struct wimax_dev*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wimax_id_table ; 
 int /*<<< orphan*/  wimax_id_table_lock ; 

void wimax_id_table_add(struct wimax_dev *wimax_dev)
{
	d_fnstart(3, NULL, "(wimax_dev %p)\n", wimax_dev);
	spin_lock(&wimax_id_table_lock);
	list_add(&wimax_dev->id_table_node, &wimax_id_table);
	spin_unlock(&wimax_id_table_lock);
	d_fnend(3, NULL, "(wimax_dev %p)\n", wimax_dev);
}