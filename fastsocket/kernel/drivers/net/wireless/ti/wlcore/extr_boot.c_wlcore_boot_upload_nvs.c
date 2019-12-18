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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct TYPE_7__ {scalar_t__ dual_mode_select; } ;
struct wl128x_nvs_file {scalar_t__ nvs; TYPE_2__ general_params; } ;
struct TYPE_6__ {scalar_t__ dual_mode_select; } ;
struct wl1271_nvs_file {scalar_t__ nvs; TYPE_1__ general_params; } ;
struct TYPE_9__ {scalar_t__ start; } ;
struct TYPE_10__ {TYPE_4__ reg; } ;
struct wl1271 {size_t* nvs; int quirks; int nvs_len; int enable_11a; int /*<<< orphan*/ * ptable; TYPE_5__ curr_part; TYPE_3__* addresses; } ;
struct TYPE_8__ {size_t* addr; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  DEBUG_BOOT ; 
 int EILSEQ ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t PART_WORK ; 
 int /*<<< orphan*/  REG_CMD_MBOX_ADDRESS ; 
 int WL1271_INI_LEGACY_NVS_FILE_SIZE ; 
 int WLCORE_QUIRK_LEGACY_NVS ; 
 int /*<<< orphan*/  kfree (size_t*) ; 
 size_t* kmemdup (size_t*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int /*<<< orphan*/  wl1271_error (char*,...) ; 
 int wlcore_set_partition (struct wl1271*,int /*<<< orphan*/ *) ; 
 int wlcore_write32 (struct wl1271*,size_t,size_t) ; 
 int wlcore_write_data (struct wl1271*,int /*<<< orphan*/ ,size_t*,size_t,int) ; 

int wlcore_boot_upload_nvs(struct wl1271 *wl)
{
	size_t nvs_len, burst_len;
	int i;
	u32 dest_addr, val;
	u8 *nvs_ptr, *nvs_aligned;
	int ret;

	if (wl->nvs == NULL) {
		wl1271_error("NVS file is needed during boot");
		return -ENODEV;
	}

	if (wl->quirks & WLCORE_QUIRK_LEGACY_NVS) {
		struct wl1271_nvs_file *nvs =
			(struct wl1271_nvs_file *)wl->nvs;
		/*
		 * FIXME: the LEGACY NVS image support (NVS's missing the 5GHz
		 * band configurations) can be removed when those NVS files stop
		 * floating around.
		 */
		if (wl->nvs_len == sizeof(struct wl1271_nvs_file) ||
		    wl->nvs_len == WL1271_INI_LEGACY_NVS_FILE_SIZE) {
			if (nvs->general_params.dual_mode_select)
				wl->enable_11a = true;
		}

		if (wl->nvs_len != sizeof(struct wl1271_nvs_file) &&
		    (wl->nvs_len != WL1271_INI_LEGACY_NVS_FILE_SIZE ||
		     wl->enable_11a)) {
			wl1271_error("nvs size is not as expected: %zu != %zu",
				wl->nvs_len, sizeof(struct wl1271_nvs_file));
			kfree(wl->nvs);
			wl->nvs = NULL;
			wl->nvs_len = 0;
			return -EILSEQ;
		}

		/* only the first part of the NVS needs to be uploaded */
		nvs_len = sizeof(nvs->nvs);
		nvs_ptr = (u8 *) nvs->nvs;
	} else {
		struct wl128x_nvs_file *nvs = (struct wl128x_nvs_file *)wl->nvs;

		if (wl->nvs_len == sizeof(struct wl128x_nvs_file)) {
			if (nvs->general_params.dual_mode_select)
				wl->enable_11a = true;
		} else {
			wl1271_error("nvs size is not as expected: %zu != %zu",
				     wl->nvs_len,
				     sizeof(struct wl128x_nvs_file));
			kfree(wl->nvs);
			wl->nvs = NULL;
			wl->nvs_len = 0;
			return -EILSEQ;
		}

		/* only the first part of the NVS needs to be uploaded */
		nvs_len = sizeof(nvs->nvs);
		nvs_ptr = (u8 *)nvs->nvs;
	}

	/* update current MAC address to NVS */
	nvs_ptr[11] = wl->addresses[0].addr[0];
	nvs_ptr[10] = wl->addresses[0].addr[1];
	nvs_ptr[6] = wl->addresses[0].addr[2];
	nvs_ptr[5] = wl->addresses[0].addr[3];
	nvs_ptr[4] = wl->addresses[0].addr[4];
	nvs_ptr[3] = wl->addresses[0].addr[5];

	/*
	 * Layout before the actual NVS tables:
	 * 1 byte : burst length.
	 * 2 bytes: destination address.
	 * n bytes: data to burst copy.
	 *
	 * This is ended by a 0 length, then the NVS tables.
	 */

	/* FIXME: Do we need to check here whether the LSB is 1? */
	while (nvs_ptr[0]) {
		burst_len = nvs_ptr[0];
		dest_addr = (nvs_ptr[1] & 0xfe) | ((u32)(nvs_ptr[2] << 8));

		/*
		 * Due to our new wl1271_translate_reg_addr function,
		 * we need to add the register partition start address
		 * to the destination
		 */
		dest_addr += wl->curr_part.reg.start;

		/* We move our pointer to the data */
		nvs_ptr += 3;

		for (i = 0; i < burst_len; i++) {
			if (nvs_ptr + 3 >= (u8 *) wl->nvs + nvs_len)
				goto out_badnvs;

			val = (nvs_ptr[0] | (nvs_ptr[1] << 8)
			       | (nvs_ptr[2] << 16) | (nvs_ptr[3] << 24));

			wl1271_debug(DEBUG_BOOT,
				     "nvs burst write 0x%x: 0x%x",
				     dest_addr, val);
			ret = wlcore_write32(wl, dest_addr, val);
			if (ret < 0)
				return ret;

			nvs_ptr += 4;
			dest_addr += 4;
		}

		if (nvs_ptr >= (u8 *) wl->nvs + nvs_len)
			goto out_badnvs;
	}

	/*
	 * We've reached the first zero length, the first NVS table
	 * is located at an aligned offset which is at least 7 bytes further.
	 * NOTE: The wl->nvs->nvs element must be first, in order to
	 * simplify the casting, we assume it is at the beginning of
	 * the wl->nvs structure.
	 */
	nvs_ptr = (u8 *)wl->nvs +
			ALIGN(nvs_ptr - (u8 *)wl->nvs + 7, 4);

	if (nvs_ptr >= (u8 *) wl->nvs + nvs_len)
		goto out_badnvs;

	nvs_len -= nvs_ptr - (u8 *)wl->nvs;

	/* Now we must set the partition correctly */
	ret = wlcore_set_partition(wl, &wl->ptable[PART_WORK]);
	if (ret < 0)
		return ret;

	/* Copy the NVS tables to a new block to ensure alignment */
	nvs_aligned = kmemdup(nvs_ptr, nvs_len, GFP_KERNEL);
	if (!nvs_aligned)
		return -ENOMEM;

	/* And finally we upload the NVS tables */
	ret = wlcore_write_data(wl, REG_CMD_MBOX_ADDRESS, nvs_aligned, nvs_len,
				false);

	kfree(nvs_aligned);
	return ret;

out_badnvs:
	wl1271_error("nvs data is malformed");
	return -EILSEQ;
}