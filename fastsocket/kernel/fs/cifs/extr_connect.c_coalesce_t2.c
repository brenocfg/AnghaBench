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
struct TYPE_4__ {int /*<<< orphan*/  DataCount; int /*<<< orphan*/  DataOffset; int /*<<< orphan*/  TotalDataCount; } ;
struct TYPE_3__ {int /*<<< orphan*/  Protocol; } ;
struct smb_t2_rsp {TYPE_2__ t2_rsp; TYPE_1__ hdr; } ;
struct smb_hdr {int /*<<< orphan*/  smb_buf_length; } ;
typedef  unsigned int __u16 ;

/* Variables and functions */
 int CIFSMaxBufSize ; 
 int ENOBUFS ; 
 int EPROTO ; 
 int MAX_CIFS_HDR_SIZE ; 
 unsigned int USHRT_MAX ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 
 unsigned int get_bcc (struct smb_hdr*) ; 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  put_bcc (unsigned int,struct smb_hdr*) ; 
 int /*<<< orphan*/  put_unaligned_le16 (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int coalesce_t2(char *second_buf, struct smb_hdr *target_hdr)
{
	struct smb_t2_rsp *pSMBs = (struct smb_t2_rsp *)second_buf;
	struct smb_t2_rsp *pSMBt  = (struct smb_t2_rsp *)target_hdr;
	char *data_area_of_tgt;
	char *data_area_of_src;
	int remaining;
	unsigned int byte_count, total_in_tgt;
	__u16 tgt_total_cnt, src_total_cnt, total_in_src;

	src_total_cnt = get_unaligned_le16(&pSMBs->t2_rsp.TotalDataCount);
	tgt_total_cnt = get_unaligned_le16(&pSMBt->t2_rsp.TotalDataCount);

	if (tgt_total_cnt != src_total_cnt)
		cFYI(1, "total data count of primary and secondary t2 differ "
			"source=%hu target=%hu", src_total_cnt, tgt_total_cnt);

	total_in_tgt = get_unaligned_le16(&pSMBt->t2_rsp.DataCount);

	remaining = tgt_total_cnt - total_in_tgt;

	if (remaining < 0) {
		cFYI(1, "Server sent too much data. tgt_total_cnt=%hu "
			"total_in_tgt=%hu", tgt_total_cnt, total_in_tgt);
		return -EPROTO;
	}

	if (remaining == 0) {
		/* nothing to do, ignore */
		cFYI(1, "no more data remains");
		return 0;
	}

	total_in_src = get_unaligned_le16(&pSMBs->t2_rsp.DataCount);
	if (remaining < total_in_src)
		cFYI(1, "transact2 2nd response contains too much data");

	/* find end of first SMB data area */
	data_area_of_tgt = (char *)&pSMBt->hdr.Protocol +
				get_unaligned_le16(&pSMBt->t2_rsp.DataOffset);

	/* validate target area */
	data_area_of_src = (char *)&pSMBs->hdr.Protocol +
				get_unaligned_le16(&pSMBs->t2_rsp.DataOffset);

	data_area_of_tgt += total_in_tgt;

	total_in_tgt += total_in_src;
	/* is the result too big for the field? */
	if (total_in_tgt > USHRT_MAX) {
		cFYI(1, "coalesced DataCount too large (%u)", total_in_tgt);
		return -EPROTO;
	}
	put_unaligned_le16(total_in_tgt, &pSMBt->t2_rsp.DataCount);

	/* fix up the BCC */
	byte_count = get_bcc(target_hdr);
	byte_count += total_in_src;
	/* is the result too big for the field? */
	if (byte_count > USHRT_MAX) {
		cFYI(1, "coalesced BCC too large (%u)", byte_count);
		return -EPROTO;
	}
	put_bcc(byte_count, target_hdr);

	byte_count = be32_to_cpu(target_hdr->smb_buf_length);
	byte_count += total_in_src;
	/* don't allow buffer to overflow */
	if (byte_count > CIFSMaxBufSize + MAX_CIFS_HDR_SIZE - 4) {
		cFYI(1, "coalesced BCC exceeds buffer size (%u)", byte_count);
		return -ENOBUFS;
	}
	target_hdr->smb_buf_length = cpu_to_be32(byte_count);

	/* copy second buffer into end of first buffer */
	memcpy(data_area_of_tgt, data_area_of_src, total_in_src);

	if (remaining != total_in_src) {
		/* more responses to go */
		cFYI(1, "waiting for more secondary responses");
		return 1;
	}

	/* we are done */
	cFYI(1, "found the last secondary response");
	return 0;
}