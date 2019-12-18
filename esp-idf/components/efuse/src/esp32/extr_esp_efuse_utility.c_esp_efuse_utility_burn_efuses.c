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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ esp_efuse_coding_scheme_t ;
struct TYPE_2__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int COUNT_EFUSE_BLOCKS ; 
 int COUNT_EFUSE_REG_PER_BLOCK ; 
 scalar_t__ EFUSE_CMD_PGM ; 
 scalar_t__ EFUSE_CMD_READ ; 
 scalar_t__ EFUSE_CMD_REG ; 
 scalar_t__ EFUSE_CODING_SCHEME_3_4 ; 
 scalar_t__ EFUSE_CONF_READ ; 
 scalar_t__ EFUSE_CONF_REG ; 
 scalar_t__ EFUSE_CONF_WRITE ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ REG_READ (scalar_t__) ; 
 int /*<<< orphan*/  REG_WRITE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ esp_efuse_get_coding_scheme (int) ; 
 int /*<<< orphan*/  esp_efuse_set_timing () ; 
 int /*<<< orphan*/  esp_efuse_utility_reset () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* range_write_addr_blocks ; 
 scalar_t__** virt_blocks ; 

void esp_efuse_utility_burn_efuses(void)
{
#ifdef CONFIG_EFUSE_VIRTUAL
    ESP_LOGW(TAG, "Virtual efuses enabled: Not really burning eFuses");
    for (int num_block = 0; num_block < COUNT_EFUSE_BLOCKS; num_block++) {
        esp_efuse_coding_scheme_t scheme = esp_efuse_get_coding_scheme(num_block);
        if (scheme == EFUSE_CODING_SCHEME_3_4) {
            uint8_t buf[COUNT_EFUSE_REG_PER_BLOCK * 4] = { 0 };
            int i = 0;
            for (uint32_t addr_wr_block = range_write_addr_blocks[num_block].start; addr_wr_block <= range_write_addr_blocks[num_block].end; addr_wr_block += 4, ++i) {
                *((uint32_t*)buf + i) = REG_READ(addr_wr_block);
            }
            int j = 0;
            uint32_t out_buf[COUNT_EFUSE_REG_PER_BLOCK] = { 0 };
            for (int k = 0; k < 4; ++k, ++j) {
                memcpy((uint8_t*)out_buf + j * 6, &buf[k * 8], 6);
            }
            for (int k = 0; k < COUNT_EFUSE_REG_PER_BLOCK; ++k) {
                REG_WRITE(range_write_addr_blocks[num_block].start + k * 4,  out_buf[k]);
            }
        }
        int subblock = 0;
        for (uint32_t addr_wr_block = range_write_addr_blocks[num_block].start; addr_wr_block <= range_write_addr_blocks[num_block].end; addr_wr_block += 4) {
            virt_blocks[num_block][subblock++] |= REG_READ(addr_wr_block);
        }
    }
#else
    esp_efuse_set_timing();
    // Permanently update values written to the efuse write registers
    REG_WRITE(EFUSE_CONF_REG, EFUSE_CONF_WRITE);
    REG_WRITE(EFUSE_CMD_REG,  EFUSE_CMD_PGM);
    while (REG_READ(EFUSE_CMD_REG) != 0) {};
    REG_WRITE(EFUSE_CONF_REG, EFUSE_CONF_READ);
    REG_WRITE(EFUSE_CMD_REG,  EFUSE_CMD_READ);
    while (REG_READ(EFUSE_CMD_REG) != 0) {};
#endif // CONFIG_EFUSE_VIRTUAL
    esp_efuse_utility_reset();
}