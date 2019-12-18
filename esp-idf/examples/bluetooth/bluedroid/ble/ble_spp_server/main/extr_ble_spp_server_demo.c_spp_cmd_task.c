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

/* Variables and functions */
 int /*<<< orphan*/  GATTS_TABLE_TAG ; 
 int /*<<< orphan*/  cmd_cmd_queue ; 
 int /*<<< orphan*/  esp_log_buffer_char (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ xQueueReceive (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void spp_cmd_task(void * arg)
{
    uint8_t * cmd_id;

    for(;;){
        vTaskDelay(50 / portTICK_PERIOD_MS);
        if(xQueueReceive(cmd_cmd_queue, &cmd_id, portMAX_DELAY)) {
            esp_log_buffer_char(GATTS_TABLE_TAG,(char *)(cmd_id),strlen((char *)cmd_id));
            free(cmd_id);
        }
    }
    vTaskDelete(NULL);
}