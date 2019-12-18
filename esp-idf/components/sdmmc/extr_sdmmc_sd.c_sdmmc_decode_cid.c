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
struct TYPE_3__ {int /*<<< orphan*/  date; int /*<<< orphan*/  serial; int /*<<< orphan*/  revision; int /*<<< orphan*/  name; int /*<<< orphan*/  oem_id; int /*<<< orphan*/  mfg_id; } ;
typedef  TYPE_1__ sdmmc_cid_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SD_CID_MDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_CID_MID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_CID_OID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_CID_PNM_CPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_CID_PSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_CID_REV (int /*<<< orphan*/ ) ; 

esp_err_t sdmmc_decode_cid(sdmmc_response_t resp, sdmmc_cid_t* out_cid)
{
    out_cid->mfg_id = SD_CID_MID(resp);
    out_cid->oem_id = SD_CID_OID(resp);
    SD_CID_PNM_CPY(resp, out_cid->name);
    out_cid->revision = SD_CID_REV(resp);
    out_cid->serial = SD_CID_PSN(resp);
    out_cid->date = SD_CID_MDT(resp);
    return ESP_OK;
}