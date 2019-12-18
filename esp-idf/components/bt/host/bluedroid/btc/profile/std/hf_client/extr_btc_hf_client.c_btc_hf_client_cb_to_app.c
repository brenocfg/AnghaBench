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
typedef  int /*<<< orphan*/  (* esp_hf_client_cb_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  esp_hf_client_cb_param_t ;
typedef  int /*<<< orphan*/  esp_hf_client_cb_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_PID_HF_CLIENT ; 
 int /*<<< orphan*/  btc_profile_cb_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void btc_hf_client_cb_to_app(esp_hf_client_cb_event_t event, esp_hf_client_cb_param_t *param)
{
    esp_hf_client_cb_t btc_hf_client_callback = (esp_hf_client_cb_t)btc_profile_cb_get(BTC_PID_HF_CLIENT);
    if (btc_hf_client_callback) {
        btc_hf_client_callback(event, param);
    }
}