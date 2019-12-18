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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct uea_softc {TYPE_1__* usb_dev; } ;
struct uea_cmvs_v2 {int dummy; } ;
struct firmware {int size; scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EILSEQ ; 
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
 int UEA_FW_NAME_MAX ; 
 int /*<<< orphan*/  cmvs_file_name (struct uea_softc*,char*,int) ; 
 scalar_t__ crc32_be (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ get_unaligned_le32 (int*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_cmvs_old (struct uea_softc*,void**,struct firmware const**) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int*,char*,int) ; 
 int /*<<< orphan*/  uea_err (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  uea_warn (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int request_cmvs(struct uea_softc *sc,
		 void **cmvs, const struct firmware **fw, int *ver)
{
	int ret, size;
	u32 crc;
	u8 *data;
	char cmv_name[UEA_FW_NAME_MAX]; /* 30 bytes stack variable */

	cmvs_file_name(sc, cmv_name, 2);
	ret = request_firmware(fw, cmv_name, &sc->usb_dev->dev);
	if (ret < 0) {
		/* if caller can handle old version, try to provide it */
		if (*ver == 1) {
			uea_warn(INS_TO_USBDEV(sc), "requesting firmware %s failed, "
				"try to get older cmvs\n", cmv_name);
			return request_cmvs_old(sc, cmvs, fw);
		}
		uea_err(INS_TO_USBDEV(sc),
		       "requesting firmware %s failed with error %d\n",
		       cmv_name, ret);
		return ret;
	}

	size = (*fw)->size;
	data = (u8 *) (*fw)->data;
	if (size < 4 || strncmp(data, "cmv2", 4) != 0) {
		if (*ver == 1) {
			uea_warn(INS_TO_USBDEV(sc), "firmware %s is corrupted, "
				"try to get older cmvs\n", cmv_name);
			release_firmware(*fw);
			return request_cmvs_old(sc, cmvs, fw);
		}
		goto err_fw_corrupted;
	}

	*ver = 2;

	data += 4;
	size -= 4;
	if (size < 5)
		goto err_fw_corrupted;

	crc = get_unaligned_le32(data);
	data += 4;
	size -= 4;
	if (crc32_be(0, data, size) != crc)
		goto err_fw_corrupted;

	if (size != *data * sizeof(struct uea_cmvs_v2) + 1)
		goto err_fw_corrupted;

	*cmvs = (void *) (data + 1);
	return *data;

err_fw_corrupted:
	uea_err(INS_TO_USBDEV(sc), "firmware %s is corrupted\n", cmv_name);
	release_firmware(*fw);
	return -EILSEQ;
}