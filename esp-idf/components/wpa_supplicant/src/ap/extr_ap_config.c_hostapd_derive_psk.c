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
typedef  int /*<<< orphan*/  u8 ;
struct hostapd_wpa_psk {int /*<<< orphan*/  psk; } ;
struct hostapd_ssid {struct hostapd_wpa_psk* wpa_psk; int /*<<< orphan*/  ssid_len; scalar_t__ ssid; scalar_t__ wpa_passphrase; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  PMK_LEN ; 
 int /*<<< orphan*/  esp_wifi_ap_get_prof_pmk_internal () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  pbkdf2_sha1 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hostapd_derive_psk(struct hostapd_ssid *ssid)
{
    ssid->wpa_psk = (struct hostapd_wpa_psk *)os_zalloc(sizeof(struct hostapd_wpa_psk));
    if (ssid->wpa_psk == NULL) {
    	wpa_printf(MSG_ERROR, "Unable to alloc space for PSK");
        return -1;
    }
    wpa_hexdump_ascii(MSG_DEBUG, "SSID",
              (u8 *) ssid->ssid, ssid->ssid_len);
    wpa_hexdump_ascii_key(MSG_DEBUG, "PSK (ASCII passphrase)",
                  (u8 *) ssid->wpa_passphrase,
                  strlen(ssid->wpa_passphrase));
#ifdef ESP_SUPPLICANT
    memcpy(ssid->wpa_psk->psk, esp_wifi_ap_get_prof_pmk_internal(), PMK_LEN);
#else
    /* It's too SLOW */
    pbkdf2_sha1(ssid->wpa_passphrase,
            ssid->ssid, ssid->ssid_len,
            4096, ssid->wpa_psk->psk, PMK_LEN);
#endif
    wpa_hexdump_key(MSG_DEBUG, "PSK (from passphrase)",
            ssid->wpa_psk->psk, PMK_LEN);
    return 0;
}