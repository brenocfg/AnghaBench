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
typedef  int uint32_t ;
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;

/* Variables and functions */
 int BIT (int) ; 
 int GPIO_ENABLE_W1TS_REG ; 
 int /*<<< orphan*/  MALLOC_CAP_DMA ; 
 scalar_t__ SLC_THRESHOLD_ADDR ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_caps_calloc (int,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sdmmc_io_write_blocks (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *,size_t const) ; 

__attribute__((used)) static void esp32_send_sip_command(sdmmc_card_t* card)
{
    printf("Test block write using CMD53\n");
    const size_t block_size = 512;
    uint8_t* data = heap_caps_calloc(1, block_size, MALLOC_CAP_DMA);
    struct sip_cmd_bootup {
            uint32_t boot_addr;
            uint32_t discard_link;
    };
    struct sip_cmd_write_reg {
            uint32_t addr;
            uint32_t val;
    };
    struct sip_hdr {
            uint8_t fc[2];
            uint16_t len;
            uint32_t cmdid;
            uint32_t seq;
    };

    struct sip_hdr* hdr = (struct sip_hdr*) data;
    size_t len;

#define SEND_WRITE_REG_CMD

#ifdef SEND_WRITE_REG_CMD
    struct sip_cmd_write_reg *write_reg = (struct sip_cmd_write_reg*) (data + sizeof(*hdr));
    len = sizeof(*hdr) + sizeof(*write_reg);
    hdr->cmdid = 3; /* SIP_CMD_WRITE_REG */
    write_reg->addr = GPIO_ENABLE_W1TS_REG;
    write_reg->val = BIT(0) | BIT(2) | BIT(4); /* Turn of RGB LEDs on WROVER-KIT */
#else
    struct sip_cmd_bootup *bootup = (struct sip_cmd_bootup*) (data + sizeof(*hdr));
    len = sizeof(*hdr) + sizeof(*bootup);
    hdr->cmdid = 5; /* SIP_CMD_BOOTUP */
    bootup->boot_addr = 0x4005a980; /* start_tb_console function in ROM */
    bootup->discard_link = 1;
#endif
    hdr->len = len;

    TEST_ESP_OK( sdmmc_io_write_blocks(card, 1, SLC_THRESHOLD_ADDR - len, data, block_size) );
    free(data);
}