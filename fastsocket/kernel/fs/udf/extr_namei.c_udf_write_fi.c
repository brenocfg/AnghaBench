#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct udf_fileident_bh {int eoffset; int soffset; TYPE_2__* sbh; TYPE_2__* ebh; } ;
struct tag {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tagChecksum; void* descCRCLength; void* descCRC; } ;
struct fileIdentDesc {int lengthFileIdent; TYPE_1__ descTag; scalar_t__ impUse; scalar_t__ padding; scalar_t__ fileIdent; int /*<<< orphan*/  lengthOfImpUse; } ;
struct TYPE_6__ {scalar_t__ i_alloc_type; } ;
struct TYPE_5__ {int* b_data; } ;

/* Variables and functions */
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 TYPE_3__* UDF_I (struct inode*) ; 
 void* cpu_to_le16 (int) ; 
 int crc_itu_t (int,int*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (TYPE_2__*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  udf_tag_checksum (TYPE_1__*) ; 

int udf_write_fi(struct inode *inode, struct fileIdentDesc *cfi,
		 struct fileIdentDesc *sfi, struct udf_fileident_bh *fibh,
		 uint8_t *impuse, uint8_t *fileident)
{
	uint16_t crclen = fibh->eoffset - fibh->soffset - sizeof(struct tag);
	uint16_t crc;
	int offset;
	uint16_t liu = le16_to_cpu(cfi->lengthOfImpUse);
	uint8_t lfi = cfi->lengthFileIdent;
	int padlen = fibh->eoffset - fibh->soffset - liu - lfi -
		sizeof(struct fileIdentDesc);
	int adinicb = 0;

	if (UDF_I(inode)->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		adinicb = 1;

	offset = fibh->soffset + sizeof(struct fileIdentDesc);

	if (impuse) {
		if (adinicb || (offset + liu < 0)) {
			memcpy((uint8_t *)sfi->impUse, impuse, liu);
		} else if (offset >= 0) {
			memcpy(fibh->ebh->b_data + offset, impuse, liu);
		} else {
			memcpy((uint8_t *)sfi->impUse, impuse, -offset);
			memcpy(fibh->ebh->b_data, impuse - offset,
				liu + offset);
		}
	}

	offset += liu;

	if (fileident) {
		if (adinicb || (offset + lfi < 0)) {
			memcpy((uint8_t *)sfi->fileIdent + liu, fileident, lfi);
		} else if (offset >= 0) {
			memcpy(fibh->ebh->b_data + offset, fileident, lfi);
		} else {
			memcpy((uint8_t *)sfi->fileIdent + liu, fileident,
				-offset);
			memcpy(fibh->ebh->b_data, fileident - offset,
				lfi + offset);
		}
	}

	offset += lfi;

	if (adinicb || (offset + padlen < 0)) {
		memset((uint8_t *)sfi->padding + liu + lfi, 0x00, padlen);
	} else if (offset >= 0) {
		memset(fibh->ebh->b_data + offset, 0x00, padlen);
	} else {
		memset((uint8_t *)sfi->padding + liu + lfi, 0x00, -offset);
		memset(fibh->ebh->b_data, 0x00, padlen + offset);
	}

	crc = crc_itu_t(0, (uint8_t *)cfi + sizeof(struct tag),
		      sizeof(struct fileIdentDesc) - sizeof(struct tag));

	if (fibh->sbh == fibh->ebh) {
		crc = crc_itu_t(crc, (uint8_t *)sfi->impUse,
			      crclen + sizeof(struct tag) -
			      sizeof(struct fileIdentDesc));
	} else if (sizeof(struct fileIdentDesc) >= -fibh->soffset) {
		crc = crc_itu_t(crc, fibh->ebh->b_data +
					sizeof(struct fileIdentDesc) +
					fibh->soffset,
			      crclen + sizeof(struct tag) -
					sizeof(struct fileIdentDesc));
	} else {
		crc = crc_itu_t(crc, (uint8_t *)sfi->impUse,
			      -fibh->soffset - sizeof(struct fileIdentDesc));
		crc = crc_itu_t(crc, fibh->ebh->b_data, fibh->eoffset);
	}

	cfi->descTag.descCRC = cpu_to_le16(crc);
	cfi->descTag.descCRCLength = cpu_to_le16(crclen);
	cfi->descTag.tagChecksum = udf_tag_checksum(&cfi->descTag);

	if (adinicb || (sizeof(struct fileIdentDesc) <= -fibh->soffset)) {
		memcpy((uint8_t *)sfi, (uint8_t *)cfi,
			sizeof(struct fileIdentDesc));
	} else {
		memcpy((uint8_t *)sfi, (uint8_t *)cfi, -fibh->soffset);
		memcpy(fibh->ebh->b_data, (uint8_t *)cfi - fibh->soffset,
		       sizeof(struct fileIdentDesc) + fibh->soffset);
	}

	if (adinicb) {
		mark_inode_dirty(inode);
	} else {
		if (fibh->sbh != fibh->ebh)
			mark_buffer_dirty_inode(fibh->ebh, inode);
		mark_buffer_dirty_inode(fibh->sbh, inode);
	}
	return 0;
}