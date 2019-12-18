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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {int dummy; } ;

/* Variables and functions */
 scalar_t__ GET_OPCODE (int*) ; 
 scalar_t__ GET_U16_FROM_CDB (int*,int /*<<< orphan*/ ) ; 
 void* GET_U8_FROM_CDB (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ MODE_SELECT ; 
 int /*<<< orphan*/  MODE_SELECT_10_CDB_PARAM_LIST_LENGTH_OFFSET ; 
 int /*<<< orphan*/  MODE_SELECT_6_CDB_PARAM_LIST_LENGTH_OFFSET ; 
 int MODE_SELECT_CDB_PAGE_FORMAT_MASK ; 
 int /*<<< orphan*/  MODE_SELECT_CDB_PAGE_FORMAT_OFFSET ; 
 int MODE_SELECT_CDB_SAVE_PAGES_MASK ; 
 int /*<<< orphan*/  MODE_SELECT_CDB_SAVE_PAGES_OFFSET ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int nvme_trans_modesel_data (struct nvme_ns*,struct sg_io_hdr*,int*,scalar_t__,int,int,int) ; 

__attribute__((used)) static int nvme_trans_mode_select(struct nvme_ns *ns, struct sg_io_hdr *hdr,
							u8 *cmd)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	u8 cdb10 = 0;
	u16 parm_list_len;
	u8 page_format;
	u8 save_pages;

	page_format = GET_U8_FROM_CDB(cmd, MODE_SELECT_CDB_PAGE_FORMAT_OFFSET);
	page_format &= MODE_SELECT_CDB_PAGE_FORMAT_MASK;

	save_pages = GET_U8_FROM_CDB(cmd, MODE_SELECT_CDB_SAVE_PAGES_OFFSET);
	save_pages &= MODE_SELECT_CDB_SAVE_PAGES_MASK;

	if (GET_OPCODE(cmd) == MODE_SELECT) {
		parm_list_len = GET_U8_FROM_CDB(cmd,
				MODE_SELECT_6_CDB_PARAM_LIST_LENGTH_OFFSET);
	} else {
		parm_list_len = GET_U16_FROM_CDB(cmd,
				MODE_SELECT_10_CDB_PARAM_LIST_LENGTH_OFFSET);
		cdb10 = 1;
	}

	if (parm_list_len != 0) {
		/*
		 * According to SPC-4 r24, a paramter list length field of 0
		 * shall not be considered an error
		 */
		res = nvme_trans_modesel_data(ns, hdr, cmd, parm_list_len,
						page_format, save_pages, cdb10);
	}

	return res;
}