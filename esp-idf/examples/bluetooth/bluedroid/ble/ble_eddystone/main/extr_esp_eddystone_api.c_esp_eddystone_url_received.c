#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int esp_err_t ;
struct TYPE_6__ {scalar_t__ tx_power; char* url; } ;
struct TYPE_5__ {TYPE_2__ url; } ;
struct TYPE_7__ {TYPE_1__ inform; } ;
typedef  TYPE_3__ esp_eddystone_result_t ;

/* Variables and functions */
 scalar_t__ EDDYSTONE_URL_MAX_LEN ; 
 scalar_t__ EDDYSTONE_URL_TX_POWER_LEN ; 
 char* esp_eddystone_resolve_url_scheme (scalar_t__ const*,scalar_t__ const*) ; 
 int /*<<< orphan*/  memcpy (char**,char*,size_t) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static esp_err_t esp_eddystone_url_received(const uint8_t* buf, uint8_t len, esp_eddystone_result_t* res)
{
    char *url_res = NULL;
    uint8_t pos = 0;
    if(len-EDDYSTONE_URL_TX_POWER_LEN > EDDYSTONE_URL_MAX_LEN) {
        //ERROR:too long url
        return -1;
    }
    res->inform.url.tx_power = buf[pos++];   
    url_res = esp_eddystone_resolve_url_scheme(buf+pos, buf+len-1);
    memcpy(&res->inform.url.url, url_res, strlen(url_res));
    res->inform.url.url[strlen(url_res)] = '\0';
    return 0;
}