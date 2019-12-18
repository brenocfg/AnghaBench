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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_WARNING (char*,int) ; 
#define  BTC_MEDIA_AUDIO_SINK_CFG_UPDATE 132 
#define  BTC_MEDIA_AUDIO_SINK_CLEAR_TRACK 131 
#define  BTC_MEDIA_FLUSH_AA_RX 130 
#define  BTC_MEDIA_TASK_SINK_CLEAN_UP 129 
#define  BTC_MEDIA_TASK_SINK_INIT 128 
 int /*<<< orphan*/  btc_a2dp_sink_handle_clear_track () ; 
 int /*<<< orphan*/  btc_a2dp_sink_handle_decoder_reset (void*) ; 
 int /*<<< orphan*/  btc_a2dp_sink_rx_flush () ; 
 int /*<<< orphan*/  btc_a2dp_sink_thread_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btc_a2dp_sink_thread_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_free (void*) ; 

__attribute__((used)) static bool btc_a2dp_sink_ctrl(uint32_t sig, void *param)
{
    switch (sig) {
    case BTC_MEDIA_TASK_SINK_INIT:
        btc_a2dp_sink_thread_init(NULL);
        break;
    case BTC_MEDIA_TASK_SINK_CLEAN_UP:
        btc_a2dp_sink_thread_cleanup(NULL);
        break;
    case BTC_MEDIA_AUDIO_SINK_CFG_UPDATE:
        btc_a2dp_sink_handle_decoder_reset(param);
        break;
    case BTC_MEDIA_AUDIO_SINK_CLEAR_TRACK:
        btc_a2dp_sink_handle_clear_track();
        break;
    case BTC_MEDIA_FLUSH_AA_RX:
        btc_a2dp_sink_rx_flush();
        break;
    default:
        APPL_TRACE_WARNING("media task unhandled evt: 0x%x\n", sig);
    }

    if (param != NULL) {
        osi_free(param);
    }

    return true;
}