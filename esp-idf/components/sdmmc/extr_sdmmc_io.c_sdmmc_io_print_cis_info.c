#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_4__ {scalar_t__ (* func ) (TYPE_1__ const*,int*,int /*<<< orphan*/ *) ;scalar_t__ code; } ;
typedef  TYPE_1__ cis_tuple_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CISTPL_CODE_END ; 
 int /*<<< orphan*/  ESP_LOG_BUFFER_HEXDUMP (char*,int*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOG_DEBUG ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ cis_tuple_func_default (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 TYPE_1__* get_tuple (int) ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ stub1 (TYPE_1__ const*,int*,int /*<<< orphan*/ *) ; 

esp_err_t sdmmc_io_print_cis_info(uint8_t* buffer, size_t buffer_size, FILE* fp)
{
    ESP_LOG_BUFFER_HEXDUMP("CIS", buffer, buffer_size, ESP_LOG_DEBUG);
    if (!fp) fp = stdout;

    uint8_t* cis = buffer;
    do {
        const cis_tuple_t* tuple = get_tuple(cis[0]);
        int size = cis[1];
        esp_err_t ret = ESP_OK;
        if (tuple) {
            ret = tuple->func(tuple, cis, fp);
        } else {
            ret = cis_tuple_func_default(NULL, cis, fp);
        }
        if (ret != ESP_OK) return ret;
        cis += 2 + size;
        if (tuple && tuple->code == CISTPL_CODE_END) break;
    } while (cis < buffer + buffer_size) ;
    return ESP_OK;
}