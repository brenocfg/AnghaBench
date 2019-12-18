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
struct alauda_media_info {unsigned int zoneshift; unsigned int blockshift; unsigned int pageshift; unsigned int capacity; int /*<<< orphan*/ ** pba_to_lba; int /*<<< orphan*/ ** lba_to_pba; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alauda_free_maps (struct alauda_media_info *media_info)
{
	unsigned int shift = media_info->zoneshift
		+ media_info->blockshift + media_info->pageshift;
	unsigned int num_zones = media_info->capacity >> shift;
	unsigned int i;

	if (media_info->lba_to_pba != NULL)
		for (i = 0; i < num_zones; i++) {
			kfree(media_info->lba_to_pba[i]);
			media_info->lba_to_pba[i] = NULL;
		}

	if (media_info->pba_to_lba != NULL)
		for (i = 0; i < num_zones; i++) {
			kfree(media_info->pba_to_lba[i]);
			media_info->pba_to_lba[i] = NULL;
		}
}