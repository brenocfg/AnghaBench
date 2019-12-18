#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ item_num; char* item_str; scalar_t__ cur_statement; } ;
typedef  TYPE_1__ esp_gps_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ STATEMENT_GGA ; 
 scalar_t__ STATEMENT_GLL ; 
 scalar_t__ STATEMENT_GSA ; 
 scalar_t__ STATEMENT_GSV ; 
 scalar_t__ STATEMENT_RMC ; 
 scalar_t__ STATEMENT_UNKNOWN ; 
 scalar_t__ STATEMENT_VTG ; 
 int /*<<< orphan*/  parse_gga (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_gll (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_gsa (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_gsv (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_rmc (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_vtg (TYPE_1__*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static esp_err_t parse_item(esp_gps_t *esp_gps)
{
    esp_err_t err = ESP_OK;
    /* start of a statement */
    if (esp_gps->item_num == 0 && esp_gps->item_str[0] == '$') {
        if (0) {
        }
#if CONFIG_NMEA_STATEMENT_GGA
        else if (strstr(esp_gps->item_str, "GGA")) {
            esp_gps->cur_statement = STATEMENT_GGA;
        }
#endif
#if CONFIG_NMEA_STATEMENT_GSA
        else if (strstr(esp_gps->item_str, "GSA")) {
            esp_gps->cur_statement = STATEMENT_GSA;
        }
#endif
#if CONFIG_NMEA_STATEMENT_RMC
        else if (strstr(esp_gps->item_str, "RMC")) {
            esp_gps->cur_statement = STATEMENT_RMC;
        }
#endif
#if CONFIG_NMEA_STATEMENT_GSV
        else if (strstr(esp_gps->item_str, "GSV")) {
            esp_gps->cur_statement = STATEMENT_GSV;
        }
#endif
#if CONFIG_NMEA_STATEMENT_GLL
        else if (strstr(esp_gps->item_str, "GLL")) {
            esp_gps->cur_statement = STATEMENT_GLL;
        }
#endif
#if CONFIG_NMEA_STATEMENT_VTG
        else if (strstr(esp_gps->item_str, "VTG")) {
            esp_gps->cur_statement = STATEMENT_VTG;
        }
#endif
        else {
            esp_gps->cur_statement = STATEMENT_UNKNOWN;
        }
        goto out;
    }
    /* Parse each item, depend on the type of the statement */
    if (esp_gps->cur_statement == STATEMENT_UNKNOWN) {
        goto out;
    }
#if CONFIG_NMEA_STATEMENT_GGA
    else if (esp_gps->cur_statement == STATEMENT_GGA) {
        parse_gga(esp_gps);
    }
#endif
#if CONFIG_NMEA_STATEMENT_GSA
    else if (esp_gps->cur_statement == STATEMENT_GSA) {
        parse_gsa(esp_gps);
    }
#endif
#if CONFIG_NMEA_STATEMENT_GSV
    else if (esp_gps->cur_statement == STATEMENT_GSV) {
        parse_gsv(esp_gps);
    }
#endif
#if CONFIG_NMEA_STATEMENT_RMC
    else if (esp_gps->cur_statement == STATEMENT_RMC) {
        parse_rmc(esp_gps);
    }
#endif
#if CONFIG_NMEA_STATEMENT_GLL
    else if (esp_gps->cur_statement == STATEMENT_GLL) {
        parse_gll(esp_gps);
    }
#endif
#if CONFIG_NMEA_STATEMENT_VTG
    else if (esp_gps->cur_statement == STATEMENT_VTG) {
        parse_vtg(esp_gps);
    }
#endif
    else {
        err =  ESP_FAIL;
    }
out:
    return err;
}