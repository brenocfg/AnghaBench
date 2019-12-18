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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  esp_efuse_coding_scheme_t ;
typedef  scalar_t__ esp_efuse_block_t ;

/* Variables and functions */
 scalar_t__ EFUSE_BLK0 ; 
 int /*<<< orphan*/  EFUSE_BLK0_RDATA6_REG ; 
 int /*<<< orphan*/  EFUSE_CODING_SCHEME ; 
 int /*<<< orphan*/  EFUSE_CODING_SCHEME_3_4 ; 
 int /*<<< orphan*/  EFUSE_CODING_SCHEME_NONE ; 
 int /*<<< orphan*/  EFUSE_CODING_SCHEME_REPEAT ; 
 int EFUSE_CODING_SCHEME_VAL_34 ; 
 int EFUSE_CODING_SCHEME_VAL_NONE ; 
 int EFUSE_CODING_SCHEME_VAL_REPEAT ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 

esp_efuse_coding_scheme_t esp_efuse_get_coding_scheme(esp_efuse_block_t blk)
{
    esp_efuse_coding_scheme_t scheme;
    if (blk == EFUSE_BLK0) {
        scheme = EFUSE_CODING_SCHEME_NONE;
    } else {
        uint32_t coding_scheme = REG_GET_FIELD(EFUSE_BLK0_RDATA6_REG, EFUSE_CODING_SCHEME);
        if (coding_scheme == EFUSE_CODING_SCHEME_VAL_NONE ||
            coding_scheme == (EFUSE_CODING_SCHEME_VAL_34 | EFUSE_CODING_SCHEME_VAL_REPEAT)) {
            scheme = EFUSE_CODING_SCHEME_NONE;
        } else if (coding_scheme == EFUSE_CODING_SCHEME_VAL_34) {
            scheme = EFUSE_CODING_SCHEME_3_4;
        } else {
            scheme = EFUSE_CODING_SCHEME_REPEAT;
        }
    }
    ESP_LOGD(TAG, "coding scheme %d", scheme);
    return scheme;
}