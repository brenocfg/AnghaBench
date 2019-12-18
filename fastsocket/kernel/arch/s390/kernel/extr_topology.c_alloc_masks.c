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
struct tl_info {int* mag; int mnest; } ;
struct mask_info {struct mask_info* next; } ;

/* Variables and functions */
 int NR_MAG ; 
 struct mask_info* alloc_bootmem (int) ; 
 int max (int,int) ; 

__attribute__((used)) static void alloc_masks(struct tl_info *info, struct mask_info *mask, int offset)
{
	int i, nr_masks;

	nr_masks = info->mag[NR_MAG - offset];
	for (i = 0; i < info->mnest - offset; i++)
		nr_masks *= info->mag[NR_MAG - offset - 1 - i];
	nr_masks = max(nr_masks, 1);
	for (i = 0; i < nr_masks; i++) {
		mask->next = alloc_bootmem(sizeof(struct mask_info));
		mask = mask->next;
	}
}