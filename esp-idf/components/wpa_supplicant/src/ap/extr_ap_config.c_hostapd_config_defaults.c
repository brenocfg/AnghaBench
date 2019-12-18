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
struct hostapd_config {int num_bss; int beacon_int; int rts_threshold; int fragm_threshold; int send_probe_response; int ap_table_max_size; int ap_table_expiration_time; int /*<<< orphan*/  ht_capab; struct hostapd_config* bss; } ;
struct hostapd_bss_config {int num_bss; int beacon_int; int rts_threshold; int fragm_threshold; int send_probe_response; int ap_table_max_size; int ap_table_expiration_time; int /*<<< orphan*/  ht_capab; struct hostapd_bss_config* bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  HT_CAP_INFO_SMPS_DISABLED ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  hostapd_config_defaults_bss (struct hostapd_config*) ; 
 int /*<<< orphan*/  os_free (struct hostapd_config*) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

struct hostapd_config * hostapd_config_defaults(void)
{
#define ecw2cw(ecw) ((1 << (ecw)) - 1)

    struct hostapd_config *conf;
    struct hostapd_bss_config *bss;
#undef ecw2cw

    conf = (struct hostapd_config *)os_zalloc(sizeof(*conf));
    bss = (struct hostapd_bss_config *)os_zalloc(sizeof(*bss));
    if (conf == NULL || bss == NULL) {
    	wpa_printf(MSG_DEBUG, "Failed to allocate memory for "
               "configuration data.");
        os_free(conf);
        os_free(bss);
        return NULL;
    }

    hostapd_config_defaults_bss(bss);

    conf->num_bss = 1;
    conf->bss = bss;

    conf->beacon_int = 100;
    conf->rts_threshold = -1; /* use driver default: 2347 */
    conf->fragm_threshold = -1; /* user driver default: 2346 */
    conf->send_probe_response = 1;

    conf->ht_capab = HT_CAP_INFO_SMPS_DISABLED;

    conf->ap_table_max_size = 255;
    conf->ap_table_expiration_time = 60;

    return conf;
}