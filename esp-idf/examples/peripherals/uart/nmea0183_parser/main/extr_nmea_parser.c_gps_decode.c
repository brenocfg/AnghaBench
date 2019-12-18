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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  gps_t ;
struct TYPE_4__ {char* buffer; int asterisk; size_t item_pos; int cur_statement; char crc; scalar_t__ sat_count; scalar_t__ sat_num; char* item_str; int parsed_statement; int all_statements; char parent; int /*<<< orphan*/  event_loop_hdl; scalar_t__ item_num; } ;
typedef  TYPE_1__ esp_gps_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ESP_NMEA_EVENT ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  GPS_TAG ; 
 int /*<<< orphan*/  GPS_UNKNOWN ; 
 int /*<<< orphan*/  GPS_UPDATE ; 
#define  STATEMENT_GGA 133 
#define  STATEMENT_GLL 132 
#define  STATEMENT_GSA 131 
#define  STATEMENT_GSV 130 
#define  STATEMENT_RMC 129 
 int STATEMENT_UNKNOWN ; 
#define  STATEMENT_VTG 128 
 int /*<<< orphan*/  esp_event_post_to (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int) ; 
 int /*<<< orphan*/  parse_item (TYPE_1__*) ; 
 int portTICK_PERIOD_MS ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static esp_err_t gps_decode(esp_gps_t *esp_gps, size_t len)
{
    const uint8_t *d = esp_gps->buffer;
    while (*d) {
        /* Start of a statement */
        if (*d == '$') {
            /* Reset runtime information */
            esp_gps->asterisk = 0;
            esp_gps->item_num = 0;
            esp_gps->item_pos = 0;
            esp_gps->cur_statement = 0;
            esp_gps->crc = 0;
            esp_gps->sat_count = 0;
            esp_gps->sat_num = 0;
            /* Add character to item */
            esp_gps->item_str[esp_gps->item_pos++] = *d;
            esp_gps->item_str[esp_gps->item_pos] = '\0';
        }
        /* Detect item separator character */
        else if (*d == ',') {
            /* Parse current item */
            parse_item(esp_gps);
            /* Add character to CRC computation */
            esp_gps->crc ^= (uint8_t)(*d);
            /* Start with next item */
            esp_gps->item_pos = 0;
            esp_gps->item_str[0] = '\0';
            esp_gps->item_num++;
        }
        /* End of CRC computation */
        else if (*d == '*') {
            /* Parse current item */
            parse_item(esp_gps);
            /* Asterisk detected */
            esp_gps->asterisk = 1;
            /* Start with next item */
            esp_gps->item_pos = 0;
            esp_gps->item_str[0] = '\0';
            esp_gps->item_num++;
        }
        /* End of statement */
        else if (*d == '\r') {
            /* Convert received CRC from string (hex) to number */
            uint8_t crc = (uint8_t)strtol(esp_gps->item_str, NULL, 16);
            /* CRC passed */
            if (esp_gps->crc == crc) {
                switch (esp_gps->cur_statement) {
#if CONFIG_NMEA_STATEMENT_GGA
                case STATEMENT_GGA:
                    esp_gps->parsed_statement |= 1 << STATEMENT_GGA;
                    break;
#endif
#if CONFIG_NMEA_STATEMENT_GSA
                case STATEMENT_GSA:
                    esp_gps->parsed_statement |= 1 << STATEMENT_GSA;
                    break;
#endif
#if CONFIG_NMEA_STATEMENT_RMC
                case STATEMENT_RMC:
                    esp_gps->parsed_statement |= 1 << STATEMENT_RMC;
                    break;
#endif
#if CONFIG_NMEA_STATEMENT_GSV
                case STATEMENT_GSV:
                    if (esp_gps->sat_num == esp_gps->sat_count) {
                        esp_gps->parsed_statement |= 1 << STATEMENT_GSV;
                    }
                    break;
#endif
#if CONFIG_NMEA_STATEMENT_GLL
                case STATEMENT_GLL:
                    esp_gps->parsed_statement |= 1 << STATEMENT_GLL;
                    break;
#endif
#if CONFIG_NMEA_STATEMENT_VTG
                case STATEMENT_VTG:
                    esp_gps->parsed_statement |= 1 << STATEMENT_VTG;
                    break;
#endif
                default:
                    break;
                }
                /* Check if all statements have been parsed */
                if (((esp_gps->parsed_statement) & esp_gps->all_statements) == esp_gps->all_statements) {
                    esp_gps->parsed_statement = 0;
                    /* Send signal to notify that GPS information has been updated */
                    esp_event_post_to(esp_gps->event_loop_hdl, ESP_NMEA_EVENT, GPS_UPDATE,
                                      &(esp_gps->parent), sizeof(gps_t), 100 / portTICK_PERIOD_MS);
                }
            } else {
                ESP_LOGD(GPS_TAG, "CRC Error for statement:%s", esp_gps->buffer);
            }
            if (esp_gps->cur_statement == STATEMENT_UNKNOWN) {
                /* Send signal to notify that one unknown statement has been met */
                esp_event_post_to(esp_gps->event_loop_hdl, ESP_NMEA_EVENT, GPS_UNKNOWN,
                                  esp_gps->buffer, len, 100 / portTICK_PERIOD_MS);
            }
        }
        /* Other non-space character */
        else {
            if (!(esp_gps->asterisk)) {
                /* Add to CRC */
                esp_gps->crc ^= (uint8_t)(*d);
            }
            /* Add character to item */
            esp_gps->item_str[esp_gps->item_pos++] = *d;
            esp_gps->item_str[esp_gps->item_pos] = '\0';
        }
        /* Process next character */
        d++;
    }
    return ESP_OK;
}