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
struct TYPE_2__ {unsigned int* fw_ver; } ;
struct wl1271 {scalar_t__ fw_type; unsigned int* min_mr_fw_ver; unsigned int* min_sr_fw_ver; TYPE_1__ chip; } ;
typedef  int /*<<< orphan*/  min_fw_str ;

/* Variables and functions */
 int EINVAL ; 
 size_t FW_VER_CHIP ; 
 size_t FW_VER_IF_TYPE ; 
 size_t FW_VER_MAJOR ; 
 size_t FW_VER_MINOR ; 
 size_t FW_VER_SUBTYPE ; 
 int NUM_FW_VER ; 
 scalar_t__ WL12XX_FW_TYPE_MULTI ; 
 unsigned int WLCORE_FW_VER_IGNORE ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  wl1271_error (char*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,char*) ; 

__attribute__((used)) static int wlcore_validate_fw_ver(struct wl1271 *wl)
{
	unsigned int *fw_ver = wl->chip.fw_ver;
	unsigned int *min_ver = (wl->fw_type == WL12XX_FW_TYPE_MULTI) ?
		wl->min_mr_fw_ver : wl->min_sr_fw_ver;
	char min_fw_str[32] = "";
	int i;

	/* the chip must be exactly equal */
	if ((min_ver[FW_VER_CHIP] != WLCORE_FW_VER_IGNORE) &&
	    (min_ver[FW_VER_CHIP] != fw_ver[FW_VER_CHIP]))
		goto fail;

	/* the firmware type must be equal */
	if ((min_ver[FW_VER_IF_TYPE] != WLCORE_FW_VER_IGNORE) &&
	    (min_ver[FW_VER_IF_TYPE] != fw_ver[FW_VER_IF_TYPE]))
		goto fail;

	/* the project number must be equal */
	if ((min_ver[FW_VER_SUBTYPE] != WLCORE_FW_VER_IGNORE) &&
	    (min_ver[FW_VER_SUBTYPE] != fw_ver[FW_VER_SUBTYPE]))
		goto fail;

	/* the API version must be greater or equal */
	if ((min_ver[FW_VER_MAJOR] != WLCORE_FW_VER_IGNORE) &&
		 (min_ver[FW_VER_MAJOR] > fw_ver[FW_VER_MAJOR]))
		goto fail;

	/* if the API version is equal... */
	if (((min_ver[FW_VER_MAJOR] == WLCORE_FW_VER_IGNORE) ||
	     (min_ver[FW_VER_MAJOR] == fw_ver[FW_VER_MAJOR])) &&
	    /* ...the minor must be greater or equal */
	    ((min_ver[FW_VER_MINOR] != WLCORE_FW_VER_IGNORE) &&
	     (min_ver[FW_VER_MINOR] > fw_ver[FW_VER_MINOR])))
		goto fail;

	return 0;

fail:
	for (i = 0; i < NUM_FW_VER; i++)
		if (min_ver[i] == WLCORE_FW_VER_IGNORE)
			snprintf(min_fw_str, sizeof(min_fw_str),
				  "%s*.", min_fw_str);
		else
			snprintf(min_fw_str, sizeof(min_fw_str),
				  "%s%u.", min_fw_str, min_ver[i]);

	wl1271_error("Your WiFi FW version (%u.%u.%u.%u.%u) is invalid.\n"
		     "Please use at least FW %s\n"
		     "You can get the latest firmwares at:\n"
		     "git://github.com/TI-OpenLink/firmwares.git",
		     fw_ver[FW_VER_CHIP], fw_ver[FW_VER_IF_TYPE],
		     fw_ver[FW_VER_MAJOR], fw_ver[FW_VER_SUBTYPE],
		     fw_ver[FW_VER_MINOR], min_fw_str);
	return -EINVAL;
}