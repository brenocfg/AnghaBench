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
struct snd_util_memhdr {int /*<<< orphan*/  block_mutex; } ;
struct snd_util_memblk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __snd_util_mem_free (struct snd_util_memhdr*,struct snd_util_memblk*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 

int snd_util_mem_free(struct snd_util_memhdr *hdr, struct snd_util_memblk *blk)
{
	if (snd_BUG_ON(!hdr || !blk))
		return -EINVAL;

	mutex_lock(&hdr->block_mutex);
	__snd_util_mem_free(hdr, blk);
	mutex_unlock(&hdr->block_mutex);
	return 0;
}