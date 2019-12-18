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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_ANCS_TAG ; 
 char* CategoryID_to_String (int) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,char*,int,char*,int,int) ; 
 char* EventID_to_String (int) ; 

void esp_receive_apple_notification_source(uint8_t *message, uint16_t message_len)
{
    if (!message || message_len < 5) {
        return;
    }

    uint8_t EventID    = message[0];
    char    *EventIDS  = EventID_to_String(EventID);
    uint8_t EventFlags = message[1];
    uint8_t CategoryID = message[2];
    char    *Cidstr    = CategoryID_to_String(CategoryID);
    uint8_t CategoryCount = message[3];
    uint32_t NotificationUID = (message[4]) | (message[5]<< 8) | (message[6]<< 16) | (message[7] << 24);
    ESP_LOGI(BLE_ANCS_TAG, "EventID:%s EventFlags:0x%x CategoryID:%s CategoryCount:%d NotificationUID:%d", EventIDS, EventFlags, Cidstr, CategoryCount, NotificationUID);
}