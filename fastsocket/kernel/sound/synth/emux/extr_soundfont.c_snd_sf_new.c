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
struct snd_util_memhdr {int dummy; } ;
struct snd_sf_callback {int dummy; } ;
struct snd_sf_list {struct snd_sf_callback callback; struct snd_util_memhdr* memhdr; int /*<<< orphan*/  lock; int /*<<< orphan*/  presets_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_sf_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_sf_init (struct snd_sf_list*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct snd_sf_list *
snd_sf_new(struct snd_sf_callback *callback, struct snd_util_memhdr *hdr)
{
	struct snd_sf_list *sflist;

	if ((sflist = kzalloc(sizeof(*sflist), GFP_KERNEL)) == NULL)
		return NULL;

	mutex_init(&sflist->presets_mutex);
	spin_lock_init(&sflist->lock);
	sflist->memhdr = hdr;

	if (callback)
		sflist->callback = *callback;

	snd_sf_init(sflist);
	return sflist;
}