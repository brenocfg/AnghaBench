#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct block_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  partition_entry_lba; int /*<<< orphan*/  sizeof_partition_entry; int /*<<< orphan*/  num_partition_entries; } ;
typedef  TYPE_1__ gpt_header ;
typedef  int /*<<< orphan*/  gpt_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (size_t,int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 size_t read_lba (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static gpt_entry *
alloc_read_gpt_entries(struct block_device *bdev, gpt_header *gpt)
{
	size_t count;
	gpt_entry *pte;
	if (!bdev || !gpt)
		return NULL;

	count = le32_to_cpu(gpt->num_partition_entries) *
                le32_to_cpu(gpt->sizeof_partition_entry);
	if (!count)
		return NULL;
	pte = kzalloc(count, GFP_KERNEL);
	if (!pte)
		return NULL;

	if (read_lba(bdev, le64_to_cpu(gpt->partition_entry_lba),
                     (u8 *) pte,
		     count) < count) {
		kfree(pte);
                pte=NULL;
		return NULL;
	}
	return pte;
}