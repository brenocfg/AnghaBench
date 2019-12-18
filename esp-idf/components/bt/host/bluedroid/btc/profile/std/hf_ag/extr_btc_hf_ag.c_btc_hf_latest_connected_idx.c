#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec {scalar_t__ tv_sec; } ;
struct TYPE_4__ {scalar_t__ tv_sec; } ;
struct TYPE_5__ {scalar_t__ connection_state; TYPE_1__ connected_timestamp; } ;
struct TYPE_6__ {TYPE_2__ btc_hf_cb; } ;

/* Variables and functions */
 int BTC_HF_INVALID_IDX ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ ESP_HF_CONNECTION_STATE_SLC_CONNECTED ; 
 int btc_max_hf_clients ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 TYPE_3__* hf_local_param ; 

__attribute__((used)) static int btc_hf_latest_connected_idx(void)
{
    struct timespec   now, conn_time_delta;
    int latest_conn_idx = BTC_HF_INVALID_IDX;
    clock_gettime(CLOCK_MONOTONIC, &now);
    conn_time_delta.tv_sec = now.tv_sec;

    for (int i = 0; i < btc_max_hf_clients; i++) {
        if (hf_local_param[i].btc_hf_cb.connection_state  == ESP_HF_CONNECTION_STATE_SLC_CONNECTED) {
            if ((now.tv_sec - hf_local_param[i].btc_hf_cb.connected_timestamp.tv_sec) < conn_time_delta.tv_sec) {
                conn_time_delta.tv_sec = now.tv_sec - hf_local_param[i].btc_hf_cb.connected_timestamp.tv_sec;
                latest_conn_idx = i;
            }
        }
    }
    return latest_conn_idx;
}