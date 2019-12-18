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
typedef  enum wpa_alg { ____Placeholder_wpa_alg } wpa_alg ;

/* Variables and functions */
 int /*<<< orphan*/  esp_wifi_set_sta_key_internal (int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int) ; 

void  wpa_install_key(enum wpa_alg alg, u8 *addr, int key_idx, int set_tx,
                      u8 *seq, size_t seq_len, u8 *key, size_t key_len, int key_entry_valid)
{
    esp_wifi_set_sta_key_internal(alg, addr, key_idx, set_tx, seq, seq_len, key, key_len, key_entry_valid);
}