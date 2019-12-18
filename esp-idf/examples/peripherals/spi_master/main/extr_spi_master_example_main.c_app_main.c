#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int clock_speed_hz; int queue_size; int /*<<< orphan*/  pre_cb; int /*<<< orphan*/  spics_io_num; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ spi_device_interface_config_t ;
typedef  int /*<<< orphan*/  spi_device_handle_t ;
struct TYPE_6__ {int quadwp_io_num; int quadhd_io_num; int max_transfer_sz; int /*<<< orphan*/  sclk_io_num; int /*<<< orphan*/  mosi_io_num; int /*<<< orphan*/  miso_io_num; } ;
typedef  TYPE_2__ spi_bus_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CHAN ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCD_HOST ; 
 int PARALLEL_LINES ; 
 int /*<<< orphan*/  PIN_NUM_CLK ; 
 int /*<<< orphan*/  PIN_NUM_CS ; 
 int /*<<< orphan*/  PIN_NUM_MISO ; 
 int /*<<< orphan*/  PIN_NUM_MOSI ; 
 int /*<<< orphan*/  display_pretty_colors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_spi_pre_transfer_callback ; 
 int /*<<< orphan*/  pretty_effect_init () ; 
 int /*<<< orphan*/  spi_bus_add_device (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_bus_initialize (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

void app_main(void)
{
    esp_err_t ret;
    spi_device_handle_t spi;
    spi_bus_config_t buscfg={
        .miso_io_num=PIN_NUM_MISO,
        .mosi_io_num=PIN_NUM_MOSI,
        .sclk_io_num=PIN_NUM_CLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=PARALLEL_LINES*320*2+8
    };
    spi_device_interface_config_t devcfg={
#ifdef CONFIG_LCD_OVERCLOCK
        .clock_speed_hz=26*1000*1000,           //Clock out at 26 MHz
#else
        .clock_speed_hz=10*1000*1000,           //Clock out at 10 MHz
#endif
        .mode=0,                                //SPI mode 0
        .spics_io_num=PIN_NUM_CS,               //CS pin
        .queue_size=7,                          //We want to be able to queue 7 transactions at a time
        .pre_cb=lcd_spi_pre_transfer_callback,  //Specify pre-transfer callback to handle D/C line
    };
    //Initialize the SPI bus
    ret=spi_bus_initialize(LCD_HOST, &buscfg, DMA_CHAN);
    ESP_ERROR_CHECK(ret);
    //Attach the LCD to the SPI bus
    ret=spi_bus_add_device(LCD_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);
    //Initialize the LCD
    lcd_init(spi);
    //Initialize the effect displayed
    ret=pretty_effect_init();
    ESP_ERROR_CHECK(ret);

    //Go do nice stuff.
    display_pretty_colors(spi);
}