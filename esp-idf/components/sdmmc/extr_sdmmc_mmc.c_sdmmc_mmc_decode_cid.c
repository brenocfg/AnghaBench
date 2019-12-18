#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sdmmc_response_t ;
struct TYPE_3__ {scalar_t__ date; void* serial; scalar_t__ revision; int /*<<< orphan*/  name; scalar_t__ oem_id; int /*<<< orphan*/  mfg_id; } ;
typedef  TYPE_1__ sdmmc_cid_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ MMC_CID_MDT_V1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMC_CID_MID_V1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMC_CID_MID_V2 (int /*<<< orphan*/ ) ; 
 scalar_t__ MMC_CID_OID_V2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMC_CID_PNM_V1_CPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* MMC_CID_PSN_V1 (int /*<<< orphan*/ ) ; 
 scalar_t__ MMC_CID_REV_V1 (int /*<<< orphan*/ ) ; 
 int MMC_CSD_MMCVER_1_0 ; 
 int MMC_CSD_MMCVER_1_4 ; 
 int MMC_CSD_MMCVER_2_0 ; 
 int MMC_CSD_MMCVER_3_1 ; 
 int MMC_CSD_MMCVER_4_0 ; 

esp_err_t sdmmc_mmc_decode_cid(int mmc_ver, sdmmc_response_t resp, sdmmc_cid_t* out_cid)
{
    if (mmc_ver == MMC_CSD_MMCVER_1_0 ||
            mmc_ver == MMC_CSD_MMCVER_1_4) {
        out_cid->mfg_id = MMC_CID_MID_V1(resp);
        out_cid->oem_id = 0;
        MMC_CID_PNM_V1_CPY(resp, out_cid->name);
        out_cid->revision = MMC_CID_REV_V1(resp);
        out_cid->serial = MMC_CID_PSN_V1(resp);
        out_cid->date = MMC_CID_MDT_V1(resp);
    } else if (mmc_ver == MMC_CSD_MMCVER_2_0 ||
            mmc_ver == MMC_CSD_MMCVER_3_1 ||
            mmc_ver == MMC_CSD_MMCVER_4_0) {
        out_cid->mfg_id = MMC_CID_MID_V2(resp);
        out_cid->oem_id = MMC_CID_OID_V2(resp);
        MMC_CID_PNM_V1_CPY(resp, out_cid->name);
        out_cid->revision = 0;
        out_cid->serial = MMC_CID_PSN_V1(resp);
        out_cid->date = 0;
    }
    return ESP_OK;
}