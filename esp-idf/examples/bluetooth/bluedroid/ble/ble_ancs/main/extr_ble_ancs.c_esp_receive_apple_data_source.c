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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_ANCS_TAG ; 
#define  CommandIDGetAppAttributes 138 
#define  CommandIDGetNotificationAttributes 137 
#define  CommandIDPerformNotificationAction 136 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
#define  NotificationAttributeIDAppIdentifier 135 
#define  NotificationAttributeIDDate 134 
#define  NotificationAttributeIDMessage 133 
#define  NotificationAttributeIDMessageSize 132 
#define  NotificationAttributeIDNegativeActionLabel 131 
#define  NotificationAttributeIDPositiveActionLabel 130 
#define  NotificationAttributeIDSubtitle 129 
#define  NotificationAttributeIDTitle 128 
 int /*<<< orphan*/  esp_log_buffer_char (char*,int*,scalar_t__) ; 
 int /*<<< orphan*/  esp_log_buffer_hex (char*,int*,scalar_t__) ; 

void esp_receive_apple_data_source(uint8_t *message, uint16_t message_len) 
{
    //esp_log_buffer_hex("data source", message, message_len);
    if (!message || message_len == 0) {
        return;
    }
    uint8_t Command_id = message[0];
    switch (Command_id)
    {
        case CommandIDGetNotificationAttributes: {
            uint32_t NotificationUID = (message[1]) | (message[2]<< 8) | (message[3]<< 16) | (message[4] << 24);
            uint32_t remian_attr_len = message_len - 5;
            uint8_t *attrs = &message[5];
            ESP_LOGI(BLE_ANCS_TAG, "recevice Notification Attributes response Command_id %d NotificationUID %d", Command_id, NotificationUID);
            while(remian_attr_len > 0) {
                uint8_t AttributeID = attrs[0];
                uint16_t len = attrs[1] | (attrs[2] << 8);
                if(len > (remian_attr_len -3)) {
                    ESP_LOGE(BLE_ANCS_TAG, "data error");
                    break;
                }
                switch (AttributeID)
                {
                    case NotificationAttributeIDAppIdentifier:
                        esp_log_buffer_char("Identifier", &attrs[3], len);
                        break;
                    case NotificationAttributeIDTitle:
                        esp_log_buffer_char("Title", &attrs[3], len);
                        break;
                    case NotificationAttributeIDSubtitle:
                        esp_log_buffer_char("Subtitle", &attrs[3], len);
                        break;
                    case NotificationAttributeIDMessage:
                        esp_log_buffer_char("Message", &attrs[3], len);
                        break;
                    case NotificationAttributeIDMessageSize:
                        esp_log_buffer_char("MessageSize", &attrs[3], len);
                        break;
                    case NotificationAttributeIDDate:
                        //yyyyMMdd'T'HHmmSS
                        esp_log_buffer_char("Date", &attrs[3], len);
                        break;
                    case NotificationAttributeIDPositiveActionLabel:
                        esp_log_buffer_hex("PActionLabel", &attrs[3], len);
                        break;
                    case NotificationAttributeIDNegativeActionLabel:
                        esp_log_buffer_hex("NActionLabel", &attrs[3], len);
                        break;
                    default:
                        esp_log_buffer_hex("unknownAttributeID", &attrs[3], len);
                        break;
                }

                attrs += (1 + 2 + len);
                remian_attr_len -= (1 + 2 + len);
            }

            break;
        }
        case CommandIDGetAppAttributes:
            ESP_LOGI(BLE_ANCS_TAG, "recevice APP Attributes response");
            break;
        case CommandIDPerformNotificationAction:
            ESP_LOGI(BLE_ANCS_TAG, "recevice Perform Notification Action");
            break;
        default:
            ESP_LOGI(BLE_ANCS_TAG, "unknown Command ID");
            break;
    }
}