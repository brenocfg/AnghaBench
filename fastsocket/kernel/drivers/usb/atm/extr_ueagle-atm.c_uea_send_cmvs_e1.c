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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  firmid; } ;
struct TYPE_4__ {TYPE_1__ phy; } ;
struct uea_softc {TYPE_2__ stats; } ;
struct uea_cmvs_v2 {int /*<<< orphan*/  data; int /*<<< orphan*/  offset; int /*<<< orphan*/  address; } ;
struct uea_cmvs_v1 {int /*<<< orphan*/  data; int /*<<< orphan*/  offset; int /*<<< orphan*/  address; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int E1_SA_CNTL ; 
 int /*<<< orphan*/  E1_SA_INFO ; 
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_cmvs (struct uea_softc*,void**,struct firmware const**,int*) ; 
 int /*<<< orphan*/  uea_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uea_info (int /*<<< orphan*/ ,char*,...) ; 
 int uea_read_cmv_e1 (struct uea_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uea_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uea_warn (int /*<<< orphan*/ ,char*) ; 
 int uea_write_cmv_e1 (struct uea_softc*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int uea_send_cmvs_e1(struct uea_softc *sc)
{
	int i, ret, len;
	void *cmvs_ptr;
	const struct firmware *cmvs_fw;
	int ver = 1; // we can handle v1 cmv firmware version;

	/* Enter in R-IDLE (cmv) until instructed otherwise */
	ret = uea_write_cmv_e1(sc, E1_SA_CNTL, 0, 1);
	if (ret < 0)
		return ret;

	/* Dump firmware version */
	ret = uea_read_cmv_e1(sc, E1_SA_INFO, 10, &sc->stats.phy.firmid);
	if (ret < 0)
		return ret;
	uea_info(INS_TO_USBDEV(sc), "ATU-R firmware version : %x\n",
			sc->stats.phy.firmid);

	/* get options */
 	ret = len = request_cmvs(sc, &cmvs_ptr, &cmvs_fw, &ver);
	if (ret < 0)
		return ret;

	/* send options */
	if (ver == 1) {
		struct uea_cmvs_v1 *cmvs_v1 = cmvs_ptr;

		uea_warn(INS_TO_USBDEV(sc), "use deprecated cmvs version, "
			"please update your firmware\n");

		for (i = 0; i < len; i++) {
			ret = uea_write_cmv_e1(sc, get_unaligned_le32(&cmvs_v1[i].address),
						get_unaligned_le16(&cmvs_v1[i].offset),
						get_unaligned_le32(&cmvs_v1[i].data));
			if (ret < 0)
				goto out;
		}
	} else if (ver == 2) {
		struct uea_cmvs_v2 *cmvs_v2 = cmvs_ptr;

		for (i = 0; i < len; i++) {
			ret = uea_write_cmv_e1(sc, get_unaligned_le32(&cmvs_v2[i].address),
						(u16) get_unaligned_le32(&cmvs_v2[i].offset),
						get_unaligned_le32(&cmvs_v2[i].data));
			if (ret < 0)
				goto out;
		}
	} else {
		/* This realy should not happen */
		uea_err(INS_TO_USBDEV(sc), "bad cmvs version %d\n", ver);
		goto out;
	}

	/* Enter in R-ACT-REQ */
	ret = uea_write_cmv_e1(sc, E1_SA_CNTL, 0, 2);
	uea_vdbg(INS_TO_USBDEV(sc), "Entering in R-ACT-REQ state\n");
	uea_info(INS_TO_USBDEV(sc), "modem started, waiting synchronization...\n");
out:
	release_firmware(cmvs_fw);
	return ret;
}