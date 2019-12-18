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
typedef  int /*<<< orphan*/  uint8_t ;
struct carlu {int /*<<< orphan*/  fw; } ;
struct carl9170fw_otus_desc {int /*<<< orphan*/  api_ver; int /*<<< orphan*/  feature_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170FW_DUMMY_FEATURE ; 
 int /*<<< orphan*/  CARL9170FW_OTUS_DESC_CUR_VER ; 
 int /*<<< orphan*/  CARL9170FW_UNUSABLE ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ OTUS_MAGIC ; 
 scalar_t__ carl9170fw_supports (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct carl9170fw_otus_desc* carlfw_find_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 

int carlu_fw_check(struct carlu *ar)
{
	struct carl9170fw_otus_desc *otus_desc;

	otus_desc = carlfw_find_desc(ar->fw, (uint8_t *) OTUS_MAGIC,
				     sizeof(*otus_desc),
				     CARL9170FW_OTUS_DESC_CUR_VER);

	if (!otus_desc) {
		err("No valid OTUS descriptor found.\n");
		return -EINVAL;
	}

	if (!carl9170fw_supports(otus_desc->feature_set, CARL9170FW_DUMMY_FEATURE)) {
		err("Invalid Firmware Descriptor.\n");
		return -EIO;
	}

	if (carl9170fw_supports(otus_desc->feature_set, CARL9170FW_UNUSABLE))
		dbg("Firmware is marked as unuseable.\n");

	info("Firmware Version: %d.\n", otus_desc->api_ver);

	return 0;
}