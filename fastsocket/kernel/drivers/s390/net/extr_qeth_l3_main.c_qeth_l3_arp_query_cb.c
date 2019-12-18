#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct qeth_reply {scalar_t__ param; } ;
struct TYPE_8__ {scalar_t__ return_code; scalar_t__ seq_no; scalar_t__ number_of_replies; } ;
struct qeth_arp_query_data {scalar_t__ no_entries; char data; int reply_bits; } ;
struct TYPE_6__ {struct qeth_arp_query_data query_arp; } ;
struct TYPE_9__ {TYPE_3__ hdr; TYPE_1__ data; } ;
struct TYPE_10__ {TYPE_4__ setassparms; } ;
struct TYPE_7__ {int return_code; int /*<<< orphan*/  prot_version; } ;
struct qeth_ipa_cmd {TYPE_5__ data; TYPE_2__ hdr; } ;
struct qeth_card {int dummy; } ;
struct qeth_arp_query_info {int mask_bits; scalar_t__ udata_len; scalar_t__ udata_offset; scalar_t__ udata; scalar_t__ no_entries; } ;
struct qeth_arp_entrytype {scalar_t__ ip; } ;
struct qeth_arp_qi_entry5 {struct qeth_arp_entrytype type; } ;
typedef  int __u8 ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 scalar_t__ QETH_QARP_MASK_OFFSET ; 
 int QETH_QARP_MEDIASPECIFIC_BYTES ; 
 int QETH_QARP_STRIP_ENTRIES ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  arpentry_matches_prot (struct qeth_arp_entrytype*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_arp_entry_size (struct qeth_card*,struct qeth_arp_query_data*,struct qeth_arp_entrytype*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int*,int) ; 

__attribute__((used)) static int qeth_l3_arp_query_cb(struct qeth_card *card,
		struct qeth_reply *reply, unsigned long data)
{
	struct qeth_ipa_cmd *cmd;
	struct qeth_arp_query_data *qdata;
	struct qeth_arp_query_info *qinfo;
	int i;
	int e;
	int entrybytes_done;
	int stripped_bytes;
	__u8 do_strip_entries;

	QETH_DBF_TEXT(TRACE, 4, "arpquecb");

	qinfo = (struct qeth_arp_query_info *) reply->param;
	cmd = (struct qeth_ipa_cmd *) data;
	if (cmd->hdr.return_code) {
		QETH_DBF_TEXT_(TRACE, 4, "arpcberr%i", cmd->hdr.return_code);
		QETH_DBF_TEXT_(TRACE, 4, "qaer1%i", cmd->hdr.return_code);
		return 0;
	}
	if (cmd->data.setassparms.hdr.return_code) {
		cmd->hdr.return_code = cmd->data.setassparms.hdr.return_code;
		QETH_DBF_TEXT_(TRACE, 4, "setaperr%i", cmd->hdr.return_code);
		QETH_DBF_TEXT_(TRACE, 4, "%i", cmd->hdr.return_code);
		return 0;
	}
	qdata = &cmd->data.setassparms.data.query_arp;
	QETH_DBF_TEXT_(TRACE, 4, "anoen%i", qdata->no_entries);

	do_strip_entries = (qinfo->mask_bits & QETH_QARP_STRIP_ENTRIES) > 0;
	stripped_bytes = do_strip_entries ? QETH_QARP_MEDIASPECIFIC_BYTES : 0;
	entrybytes_done = 0;
	for (e = 0; e < qdata->no_entries; ++e) {
		char *cur_entry;
		__u32 esize;
		struct qeth_arp_entrytype *etype;

		cur_entry = &qdata->data + entrybytes_done;
		etype = &((struct qeth_arp_qi_entry5 *) cur_entry)->type;
		if (!arpentry_matches_prot(etype, cmd->hdr.prot_version)) {
			QETH_DBF_TEXT(TRACE, 4, "pmis");
			QETH_DBF_TEXT_(TRACE, 4, "%i", etype->ip);
			break;
		}
		esize = get_arp_entry_size(card, qdata, etype,
			do_strip_entries);
		QETH_DBF_TEXT_(TRACE, 5, "esz%i", esize);
		if (!esize) {
			break;
		}
		if ((qinfo->udata_len - qinfo->udata_offset) < esize) {
			QETH_DBF_TEXT_(TRACE, 4, "qaer3%i", -ENOMEM);
			cmd->hdr.return_code = -ENOMEM;
			goto out_error;
		}

		memcpy(qinfo->udata + qinfo->udata_offset,
			&qdata->data + entrybytes_done + stripped_bytes,
			esize);
		entrybytes_done += esize + stripped_bytes;
		qinfo->udata_offset += esize;
		++qinfo->no_entries;
	}
	/* check if all replies received ... */
	if (cmd->data.setassparms.hdr.seq_no <
	    cmd->data.setassparms.hdr.number_of_replies)
		return 1;
	QETH_DBF_TEXT_(TRACE, 4, "nove%i", qinfo->no_entries);
	memcpy(qinfo->udata, &qinfo->no_entries, 4);
	/* keep STRIP_ENTRIES flag so the user program can distinguish
	 * stripped entries from normal ones */
	if (qinfo->mask_bits & QETH_QARP_STRIP_ENTRIES)
		qdata->reply_bits |= QETH_QARP_STRIP_ENTRIES;
	memcpy(qinfo->udata + QETH_QARP_MASK_OFFSET, &qdata->reply_bits, 2);
	return 0;
out_error:
	i = 0;
	memcpy(qinfo->udata, &i, 4);
	return 0;
}