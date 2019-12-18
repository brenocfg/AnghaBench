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

/* Variables and functions */
 int WIFI_CIPHER_TYPE_CCMP ; 
 int WIFI_CIPHER_TYPE_NONE ; 
 int WIFI_CIPHER_TYPE_TKIP ; 
 int WIFI_CIPHER_TYPE_TKIP_CCMP ; 
 int WIFI_CIPHER_TYPE_UNKNOWN ; 
 int WIFI_CIPHER_TYPE_WEP104 ; 
 int WIFI_CIPHER_TYPE_WEP40 ; 
#define  WPA_CIPHER_CCMP 132 
#define  WPA_CIPHER_NONE 131 
#define  WPA_CIPHER_TKIP 130 
#define  WPA_CIPHER_WEP104 129 
#define  WPA_CIPHER_WEP40 128 

int cipher_type_map(int wpa_cipher)
{
    switch (wpa_cipher) {
    case WPA_CIPHER_NONE:
        return WIFI_CIPHER_TYPE_NONE;

    case WPA_CIPHER_WEP40:
        return WIFI_CIPHER_TYPE_WEP40;

    case WPA_CIPHER_WEP104:
        return WIFI_CIPHER_TYPE_WEP104;

    case WPA_CIPHER_TKIP:
        return WIFI_CIPHER_TYPE_TKIP;

    case WPA_CIPHER_CCMP:
        return WIFI_CIPHER_TYPE_CCMP;

    case WPA_CIPHER_CCMP|WPA_CIPHER_TKIP:
        return WIFI_CIPHER_TYPE_TKIP_CCMP;

    default:
        return WIFI_CIPHER_TYPE_UNKNOWN;
    }
}