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
struct list_head {struct list_head* next; } ;
struct snd_util_memhdr {struct list_head block; } ;

/* Variables and functions */
 struct snd_util_memhdr* get_memblk (struct list_head*) ; 
 int /*<<< orphan*/  kfree (struct snd_util_memhdr*) ; 
 int /*<<< orphan*/  list_del (struct list_head*) ; 

void snd_util_memhdr_free(struct snd_util_memhdr *hdr)
{
	struct list_head *p;

	if (!hdr)
		return;
	/* release all blocks */
	while ((p = hdr->block.next) != &hdr->block) {
		list_del(p);
		kfree(get_memblk(p));
	}
	kfree(hdr);
}