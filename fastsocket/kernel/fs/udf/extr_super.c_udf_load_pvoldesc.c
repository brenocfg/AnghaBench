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
typedef  scalar_t__ uint16_t ;
struct ustr {int u_len; int /*<<< orphan*/  u_name; } ;
struct timestamp {int /*<<< orphan*/  typeAndTimezone; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  month; int /*<<< orphan*/  year; } ;
struct super_block {int dummy; } ;
struct primaryVolDesc {int /*<<< orphan*/  volSetIdent; int /*<<< orphan*/  volIdent; struct timestamp recordingDateAndTime; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_volume_ident; int /*<<< orphan*/  s_record_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ TAG_IDENT_PVD ; 
 TYPE_1__* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  kfree (struct ustr*) ; 
 struct ustr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ udf_CS0toUTF8 (struct ustr*,struct ustr*) ; 
 int /*<<< orphan*/  udf_build_ustr (struct ustr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udf_debug (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ udf_disk_stamp_to_time (int /*<<< orphan*/ *,struct timestamp) ; 
 struct buffer_head* udf_read_tagged (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int udf_load_pvoldesc(struct super_block *sb, sector_t block)
{
	struct primaryVolDesc *pvoldesc;
	struct ustr *instr, *outstr;
	struct buffer_head *bh;
	uint16_t ident;
	int ret = 1;

	instr = kmalloc(sizeof(struct ustr), GFP_NOFS);
	if (!instr)
		return 1;

	outstr = kmalloc(sizeof(struct ustr), GFP_NOFS);
	if (!outstr)
		goto out1;

	bh = udf_read_tagged(sb, block, block, &ident);
	if (!bh)
		goto out2;

	BUG_ON(ident != TAG_IDENT_PVD);

	pvoldesc = (struct primaryVolDesc *)bh->b_data;

	if (udf_disk_stamp_to_time(&UDF_SB(sb)->s_record_time,
			      pvoldesc->recordingDateAndTime)) {
#ifdef UDFFS_DEBUG
		struct timestamp *ts = &pvoldesc->recordingDateAndTime;
		udf_debug("recording time %04u/%02u/%02u"
			  " %02u:%02u (%x)\n",
			  le16_to_cpu(ts->year), ts->month, ts->day, ts->hour,
			  ts->minute, le16_to_cpu(ts->typeAndTimezone));
#endif
	}

	if (!udf_build_ustr(instr, pvoldesc->volIdent, 32))
		if (udf_CS0toUTF8(outstr, instr)) {
			strncpy(UDF_SB(sb)->s_volume_ident, outstr->u_name,
				outstr->u_len > 31 ? 31 : outstr->u_len);
			udf_debug("volIdent[] = '%s'\n",
					UDF_SB(sb)->s_volume_ident);
		}

	if (!udf_build_ustr(instr, pvoldesc->volSetIdent, 128))
		if (udf_CS0toUTF8(outstr, instr))
			udf_debug("volSetIdent[] = '%s'\n", outstr->u_name);

	brelse(bh);
	ret = 0;
out2:
	kfree(outstr);
out1:
	kfree(instr);
	return ret;
}