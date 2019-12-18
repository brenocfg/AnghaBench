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
struct snd_sf_list {int open_client; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int close_patch (struct snd_sf_list*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
snd_soundfont_close_check(struct snd_sf_list *sflist, int client)
{
	unsigned long flags;
	spin_lock_irqsave(&sflist->lock, flags);
	if (sflist->open_client == client)  {
		spin_unlock_irqrestore(&sflist->lock, flags);
		return close_patch(sflist);
	}
	spin_unlock_irqrestore(&sflist->lock, flags);
	return 0;
}