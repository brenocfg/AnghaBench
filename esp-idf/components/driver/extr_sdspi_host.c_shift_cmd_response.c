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
typedef  int uint8_t ;
struct TYPE_3__ {int r1; } ;
typedef  TYPE_1__ sdspi_hw_cmd_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 
 int SDSPI_CMD_SIZE ; 
 int SD_SPI_R1_NO_RESPONSE ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static esp_err_t shift_cmd_response(sdspi_hw_cmd_t* cmd, int sent_bytes)
{
    uint8_t* pr1 = &cmd->r1;
    int ncr_cnt = 1;
    while(true) {
        if ((*pr1 & SD_SPI_R1_NO_RESPONSE) == 0) break;
        pr1++;
        if (++ncr_cnt > 8) return ESP_ERR_NOT_FOUND;
    }

    int copy_bytes = sent_bytes - SDSPI_CMD_SIZE - ncr_cnt;
    if (copy_bytes > 0) {
        memcpy(&cmd->r1, pr1, copy_bytes);
    }

    return ESP_OK;
}