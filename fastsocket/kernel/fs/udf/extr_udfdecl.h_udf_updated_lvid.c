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
struct super_block {int s_dirt; } ;
struct logicalVolIntegrityDesc {scalar_t__ integrityType; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {int s_lvid_dirty; struct buffer_head* s_lvid_bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  LVID_INTEGRITY_TYPE_OPEN ; 
 TYPE_1__* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void udf_updated_lvid(struct super_block *sb)
{
	struct buffer_head *bh = UDF_SB(sb)->s_lvid_bh;

	BUG_ON(!bh);
	WARN_ON_ONCE(((struct logicalVolIntegrityDesc *)
		     bh->b_data)->integrityType !=
		     cpu_to_le32(LVID_INTEGRITY_TYPE_OPEN));
	sb->s_dirt = 1;
	UDF_SB(sb)->s_lvid_dirty = 1;
}