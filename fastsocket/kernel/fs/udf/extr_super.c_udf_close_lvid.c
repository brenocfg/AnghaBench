#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct udf_sb_info {scalar_t__ s_udfrev; scalar_t__ s_lvid_dirty; struct buffer_head* s_lvid_bh; } ;
struct tag {int dummy; } ;
struct super_block {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * identSuffix; } ;
struct logicalVolIntegrityDescImpUse {void* minUDFWriteRev; void* minUDFReadRev; void* maxUDFWriteRev; TYPE_1__ impIdent; } ;
struct TYPE_4__ {int /*<<< orphan*/  tagChecksum; void* descCRCLength; void* descCRC; } ;
struct logicalVolIntegrityDesc {TYPE_2__ descTag; int /*<<< orphan*/  integrityType; int /*<<< orphan*/  recordingDateAndTime; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int /*<<< orphan*/  LVID_INTEGRITY_TYPE_CLOSE ; 
 scalar_t__ UDF_MAX_WRITE_VERSION ; 
 int /*<<< orphan*/  UDF_OS_CLASS_UNIX ; 
 int /*<<< orphan*/  UDF_OS_ID_LINUX ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ crc_itu_t (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ le16_to_cpu (void*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 struct logicalVolIntegrityDescImpUse* udf_sb_lvidiu (struct udf_sb_info*) ; 
 int /*<<< orphan*/  udf_tag_checksum (TYPE_2__*) ; 
 int /*<<< orphan*/  udf_time_to_disk_stamp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udf_close_lvid(struct super_block *sb)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct buffer_head *bh = sbi->s_lvid_bh;
	struct logicalVolIntegrityDesc *lvid;
	struct logicalVolIntegrityDescImpUse *lvidiu;

	if (!bh)
		return;

	lvid = (struct logicalVolIntegrityDesc *)bh->b_data;
	lvidiu = udf_sb_lvidiu(sbi);
	lvidiu->impIdent.identSuffix[0] = UDF_OS_CLASS_UNIX;
	lvidiu->impIdent.identSuffix[1] = UDF_OS_ID_LINUX;
	udf_time_to_disk_stamp(&lvid->recordingDateAndTime, CURRENT_TIME);
	if (UDF_MAX_WRITE_VERSION > le16_to_cpu(lvidiu->maxUDFWriteRev))
		lvidiu->maxUDFWriteRev = cpu_to_le16(UDF_MAX_WRITE_VERSION);
	if (sbi->s_udfrev > le16_to_cpu(lvidiu->minUDFReadRev))
		lvidiu->minUDFReadRev = cpu_to_le16(sbi->s_udfrev);
	if (sbi->s_udfrev > le16_to_cpu(lvidiu->minUDFWriteRev))
		lvidiu->minUDFWriteRev = cpu_to_le16(sbi->s_udfrev);
	lvid->integrityType = cpu_to_le32(LVID_INTEGRITY_TYPE_CLOSE);

	lvid->descTag.descCRC = cpu_to_le16(
			crc_itu_t(0, (char *)lvid + sizeof(struct tag),
				le16_to_cpu(lvid->descTag.descCRCLength)));

	lvid->descTag.tagChecksum = udf_tag_checksum(&lvid->descTag);
	mark_buffer_dirty(bh);
	sbi->s_lvid_dirty = 0;
}