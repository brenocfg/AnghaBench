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
struct devnode {int /*<<< orphan*/  dn_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  mac_devfsdirent_label_alloc () ; 

void
mac_devfs_label_init(struct devnode *de)
{

	de->dn_label = mac_devfsdirent_label_alloc();
}