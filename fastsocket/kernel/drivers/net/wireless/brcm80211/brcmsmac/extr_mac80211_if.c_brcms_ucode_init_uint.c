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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct firmware_hdr {int /*<<< orphan*/  len; int /*<<< orphan*/  offset; int /*<<< orphan*/  idx; } ;
struct TYPE_8__ {int fw_cnt; int* hdr_num_entries; TYPE_2__** fw_bin; TYPE_1__** fw_hdr; } ;
struct brcms_info {TYPE_5__* wlc; TYPE_3__ fw; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_10__ {TYPE_4__* hw; } ;
struct TYPE_9__ {int /*<<< orphan*/  d11core; } ;
struct TYPE_7__ {int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMSG ; 
 int /*<<< orphan*/  brcms_err (int /*<<< orphan*/ ,char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

int brcms_ucode_init_uint(struct brcms_info *wl, size_t *n_bytes, u32 idx)
{
	int i, entry;
	const u8 *pdata;
	struct firmware_hdr *hdr;
	for (i = 0; i < wl->fw.fw_cnt; i++) {
		hdr = (struct firmware_hdr *)wl->fw.fw_hdr[i]->data;
		for (entry = 0; entry < wl->fw.hdr_num_entries[i];
		     entry++, hdr++) {
			if (le32_to_cpu(hdr->idx) == idx) {
				pdata = wl->fw.fw_bin[i]->data +
					le32_to_cpu(hdr->offset);
				if (le32_to_cpu(hdr->len) != 4) {
					brcms_err(wl->wlc->hw->d11core,
						  "ERROR: fw hdr len\n");
					return -ENOMSG;
				}
				*n_bytes = le32_to_cpu(*((__le32 *) pdata));
				return 0;
			}
		}
	}
	brcms_err(wl->wlc->hw->d11core,
		  "ERROR: ucode tag:%d can not be found!\n", idx);
	return -ENOMSG;
}