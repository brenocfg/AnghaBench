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
struct em28xx {int /*<<< orphan*/  devlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  em28xx_devlist_mutex ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void em28xx_remove_from_devlist(struct em28xx *dev)
{
	mutex_lock(&em28xx_devlist_mutex);
	list_del(&dev->devlist);
	mutex_unlock(&em28xx_devlist_mutex);
}