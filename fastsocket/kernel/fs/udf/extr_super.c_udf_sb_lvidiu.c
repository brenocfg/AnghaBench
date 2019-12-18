#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct udf_sb_info {TYPE_1__* s_lvid_bh; } ;
struct logicalVolIntegrityDescImpUse {int dummy; } ;
struct logicalVolIntegrityDesc {int /*<<< orphan*/ * impUse; int /*<<< orphan*/  numOfPartitions; } ;
typedef  int __u32 ;
struct TYPE_2__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

struct logicalVolIntegrityDescImpUse *udf_sb_lvidiu(struct udf_sb_info *sbi)
{
	struct logicalVolIntegrityDesc *lvid =
		(struct logicalVolIntegrityDesc *)sbi->s_lvid_bh->b_data;
	__u32 number_of_partitions = le32_to_cpu(lvid->numOfPartitions);
	__u32 offset = number_of_partitions * 2 *
				sizeof(uint32_t)/sizeof(uint8_t);
	return (struct logicalVolIntegrityDescImpUse *)&(lvid->impUse[offset]);
}