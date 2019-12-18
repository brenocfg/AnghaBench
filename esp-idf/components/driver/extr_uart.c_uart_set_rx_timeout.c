#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t uart_port_t ;
typedef  void* tout_thresh ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {int rx_tout_thrhd; int rx_tout_en; } ;
struct TYPE_6__ {void* rx_tout_thrhd; } ;
struct TYPE_5__ {scalar_t__ tick_ref_always_on; } ;
struct TYPE_8__ {TYPE_3__ conf1; TYPE_2__ mem_conf; TYPE_1__ conf0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_4__** UART ; 
 int /*<<< orphan*/  UART_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_ENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UART_EXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 size_t UART_NUM_MAX ; 
 int const UART_RX_TOUT_THRHD_V ; 
 int const UART_TOUT_REF_FACTOR_DEFAULT ; 
 int /*<<< orphan*/ * uart_spinlock ; 

esp_err_t uart_set_rx_timeout(uart_port_t uart_num, const uint8_t tout_thresh)
{
    UART_CHECK((uart_num < UART_NUM_MAX), "uart_num error", ESP_ERR_INVALID_ARG);
    UART_CHECK((tout_thresh < 127), "tout_thresh max value is 126", ESP_ERR_INVALID_ARG);
    UART_ENTER_CRITICAL(&uart_spinlock[uart_num]);
    // The tout_thresh = 1, defines TOUT interrupt timeout equal to
    // transmission time of one symbol (~11 bit) on current baudrate
    if (tout_thresh > 0) {
#if CONFIG_IDF_TARGET_ESP32
        //ESP32 hardware issue workaround: when using ref_tick, the rx timeout threshold needs increase to 10 times.
        //T_ref = T_apb * APB_CLK/(REF_TICK << CLKDIV_FRAG_BIT_WIDTH)
        if (UART[uart_num]->conf0.tick_ref_always_on == 0) {
            UART[uart_num]->conf1.rx_tout_thrhd = ((tout_thresh * UART_TOUT_REF_FACTOR_DEFAULT) & UART_RX_TOUT_THRHD_V);
        } else {
            UART[uart_num]->conf1.rx_tout_thrhd = ((tout_thresh) & UART_RX_TOUT_THRHD_V);
        }
#elif CONFIG_IDF_TARGET_ESP32S2BETA
        UART[uart_num]->mem_conf.rx_tout_thrhd = ((tout_thresh) & UART_RX_TOUT_THRHD_V);
#endif
        UART[uart_num]->conf1.rx_tout_en = 1;
    } else {
        UART[uart_num]->conf1.rx_tout_en = 0;
    }
    UART_EXIT_CRITICAL(&uart_spinlock[uart_num]);
    return ESP_OK;
}