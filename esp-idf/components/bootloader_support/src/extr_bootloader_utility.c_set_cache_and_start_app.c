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
typedef  void (* entry_t ) () ;

/* Variables and functions */
 int /*<<< orphan*/  Cache_Flush (int /*<<< orphan*/ ) ; 
 int Cache_Ibus_MMU_Set (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  Cache_Invalidate_ICache_All () ; 
 int /*<<< orphan*/  Cache_Read_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cache_Read_Enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Cache_Resume_ICache (int) ; 
 int Cache_Suspend_ICache () ; 
 int /*<<< orphan*/  DPORT_APP_CACHE_CTRL1_REG ; 
 int DPORT_APP_CACHE_MASK_DRAM1 ; 
 int DPORT_APP_CACHE_MASK_DROM0 ; 
 int DPORT_APP_CACHE_MASK_IRAM0 ; 
 int DPORT_APP_CACHE_MASK_IRAM1 ; 
 int DPORT_APP_CACHE_MASK_IROM0 ; 
 int /*<<< orphan*/  DPORT_CACHE_SOURCE_1_REG ; 
 int /*<<< orphan*/  DPORT_FLASH_MMU_TABLE_INVALID_VAL ; 
 int DPORT_FLASH_MMU_TABLE_SIZE ; 
 int /*<<< orphan*/  DPORT_MMU_ACCESS_FLASH ; 
 int /*<<< orphan*/  DPORT_PRO_CACHE_CTRL1_REG ; 
 int /*<<< orphan*/  DPORT_PRO_CACHE_I_SOURCE_PRO_IRAM1 ; 
 int /*<<< orphan*/  DPORT_PRO_CACHE_I_SOURCE_PRO_IROM0 ; 
 int DPORT_PRO_CACHE_MASK_DRAM1 ; 
 int DPORT_PRO_CACHE_MASK_DROM0 ; 
 int DPORT_PRO_CACHE_MASK_IRAM0 ; 
 int DPORT_PRO_CACHE_MASK_IRAM1 ; 
 int DPORT_PRO_CACHE_MASK_IROM0 ; 
 int /*<<< orphan*/ * DPORT_PRO_FLASH_MMU_TABLE ; 
 int /*<<< orphan*/  DPORT_PRO_ICACHE_CTRL1_REG ; 
 int DPORT_PRO_ICACHE_MASK_DROM0 ; 
 int DPORT_PRO_ICACHE_MASK_IRAM0 ; 
 int DPORT_PRO_ICACHE_MASK_IRAM1 ; 
 int DPORT_PRO_ICACHE_MASK_IROM0 ; 
 int /*<<< orphan*/  DPORT_REG_CLR_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,int,...) ; 
 int IRAM0_ADDRESS_LOW ; 
 int IRAM1_ADDRESS_LOW ; 
 int IROM0_ADDRESS_LOW ; 
 int MMU_FLASH_MASK ; 
 int /*<<< orphan*/  REG_CLR_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int bootloader_cache_pages_to_map (int,int) ; 
 int cache_flash_mmu_set (int,int /*<<< orphan*/ ,int,int,int,int) ; 
 void stub1 () ; 

__attribute__((used)) static void set_cache_and_start_app(
    uint32_t drom_addr,
    uint32_t drom_load_addr,
    uint32_t drom_size,
    uint32_t irom_addr,
    uint32_t irom_load_addr,
    uint32_t irom_size,
    uint32_t entry_addr)
{
    int rc;
    ESP_LOGD(TAG, "configure drom and irom and start");
#if CONFIG_IDF_TARGET_ESP32
    Cache_Read_Disable(0);
    Cache_Flush(0);
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    uint32_t autoload = Cache_Suspend_ICache();
    Cache_Invalidate_ICache_All();
#endif

    /* Clear the MMU entries that are already set up,
       so the new app only has the mappings it creates.
    */
    for (int i = 0; i < DPORT_FLASH_MMU_TABLE_SIZE; i++) {
        DPORT_PRO_FLASH_MMU_TABLE[i] = DPORT_FLASH_MMU_TABLE_INVALID_VAL;
    }

    uint32_t drom_load_addr_aligned = drom_load_addr & MMU_FLASH_MASK;
    uint32_t drom_page_count = bootloader_cache_pages_to_map(drom_size, drom_load_addr);
    ESP_LOGV(TAG, "d mmu set paddr=%08x vaddr=%08x size=%d n=%d",
             drom_addr & MMU_FLASH_MASK, drom_load_addr_aligned, drom_size, drom_page_count);
#if CONFIG_IDF_TARGET_ESP32
    rc = cache_flash_mmu_set(0, 0, drom_load_addr_aligned, drom_addr & MMU_FLASH_MASK, 64, drom_page_count);
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    rc = Cache_Ibus_MMU_Set(DPORT_MMU_ACCESS_FLASH, drom_load_addr & 0xffff0000, drom_addr & 0xffff0000,
                                64, drom_page_count, 0);
#endif
    ESP_LOGV(TAG, "rc=%d", rc);
#if CONFIG_IDF_TARGET_ESP32 && !CONFIG_FREERTOS_UNICORE
    rc = cache_flash_mmu_set(1, 0, drom_load_addr_aligned, drom_addr & MMU_FLASH_MASK, 64, drom_page_count);
    ESP_LOGV(TAG, "rc=%d", rc);
#endif
    uint32_t irom_load_addr_aligned = irom_load_addr & MMU_FLASH_MASK;
    uint32_t irom_page_count = bootloader_cache_pages_to_map(irom_size, irom_load_addr);
    ESP_LOGV(TAG, "i mmu set paddr=%08x vaddr=%08x size=%d n=%d",
             irom_addr & MMU_FLASH_MASK, irom_load_addr_aligned, irom_size, irom_page_count);
#if CONFIG_IDF_TARGET_ESP32
    rc = cache_flash_mmu_set(0, 0, irom_load_addr_aligned, irom_addr & MMU_FLASH_MASK, 64, irom_page_count);
    ESP_LOGV(TAG, "rc=%d", rc);
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    uint32_t iram1_used = 0, irom0_used = 0;
    if (irom_load_addr + irom_size > IRAM1_ADDRESS_LOW) {
        iram1_used = 1;
    }
    if (irom_load_addr + irom_size > IROM0_ADDRESS_LOW) {
        irom0_used = 1;
    }
    if (iram1_used || irom0_used) {
        rc = Cache_Ibus_MMU_Set(DPORT_MMU_ACCESS_FLASH, IRAM0_ADDRESS_LOW, 0, 64, 64, 1);
        rc = Cache_Ibus_MMU_Set(DPORT_MMU_ACCESS_FLASH, IRAM1_ADDRESS_LOW, 0, 64, 64, 1);
        REG_SET_BIT(DPORT_CACHE_SOURCE_1_REG, DPORT_PRO_CACHE_I_SOURCE_PRO_IRAM1);
        REG_CLR_BIT(DPORT_PRO_ICACHE_CTRL1_REG, DPORT_PRO_ICACHE_MASK_IRAM1);
        if (irom0_used) {
            rc = Cache_Ibus_MMU_Set(DPORT_MMU_ACCESS_FLASH, IROM0_ADDRESS_LOW, 0, 64, 64, 1);
            REG_SET_BIT(DPORT_CACHE_SOURCE_1_REG, DPORT_PRO_CACHE_I_SOURCE_PRO_IROM0);
            REG_CLR_BIT(DPORT_PRO_ICACHE_CTRL1_REG, DPORT_PRO_ICACHE_MASK_IROM0);
        }
    }
    rc = Cache_Ibus_MMU_Set(DPORT_MMU_ACCESS_FLASH, irom_load_addr & 0xffff0000, irom_addr & 0xffff0000, 64, irom_page_count, 0);
#endif
    ESP_LOGV(TAG, "rc=%d", rc);
#if CONFIG_IDF_TARGET_ESP32
#if !CONFIG_FREERTOS_UNICORE
    rc = cache_flash_mmu_set(1, 0, irom_load_addr_aligned, irom_addr & MMU_FLASH_MASK, 64, irom_page_count);
    ESP_LOGV(TAG, "rc=%d", rc);
#endif
    DPORT_REG_CLR_BIT( DPORT_PRO_CACHE_CTRL1_REG,
                       (DPORT_PRO_CACHE_MASK_IRAM0) | (DPORT_PRO_CACHE_MASK_IRAM1 & 0) |
                       (DPORT_PRO_CACHE_MASK_IROM0 & 0) | DPORT_PRO_CACHE_MASK_DROM0 |
                       DPORT_PRO_CACHE_MASK_DRAM1 );
#if !CONFIG_FREERTOS_UNICORE
    DPORT_REG_CLR_BIT( DPORT_APP_CACHE_CTRL1_REG,
                       (DPORT_APP_CACHE_MASK_IRAM0) | (DPORT_APP_CACHE_MASK_IRAM1 & 0) |
                       (DPORT_APP_CACHE_MASK_IROM0 & 0) | DPORT_APP_CACHE_MASK_DROM0 |
                       DPORT_APP_CACHE_MASK_DRAM1 );
#endif
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    DPORT_REG_CLR_BIT( DPORT_PRO_ICACHE_CTRL1_REG, (DPORT_PRO_ICACHE_MASK_IRAM0) | (DPORT_PRO_ICACHE_MASK_IRAM1 & 0) | (DPORT_PRO_ICACHE_MASK_IROM0 & 0) | DPORT_PRO_ICACHE_MASK_DROM0 );
#endif
#if CONFIG_IDF_TARGET_ESP32
    Cache_Read_Enable(0);
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    Cache_Resume_ICache(autoload);
#endif
    // Application will need to do Cache_Flush(1) and Cache_Read_Enable(1)

    ESP_LOGD(TAG, "start: 0x%08x", entry_addr);
    typedef void (*entry_t)(void) __attribute__((noreturn));
    entry_t entry = ((entry_t) entry_addr);

    // TODO: we have used quite a bit of stack at this point.
    // use "movsp" instruction to reset stack back to where ROM stack starts.
    (*entry)();
}