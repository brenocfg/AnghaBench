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
struct rsxx_cardinfo {int /*<<< orphan*/  dev_lock; scalar_t__ bdev_attached; int /*<<< orphan*/  gendisk; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void rsxx_detach_dev(struct rsxx_cardinfo *card)
{
	mutex_lock(&card->dev_lock);

	if (card->bdev_attached) {
		del_gendisk(card->gendisk);
		card->bdev_attached = 0;
	}

	mutex_unlock(&card->dev_lock);
}