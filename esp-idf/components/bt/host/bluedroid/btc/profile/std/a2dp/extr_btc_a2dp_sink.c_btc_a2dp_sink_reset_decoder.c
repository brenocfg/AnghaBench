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
struct TYPE_4__ {int /*<<< orphan*/  codec_info; } ;
typedef  TYPE_1__ tBTC_MEDIA_SINK_CFG_UPDATE ;
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  APPL_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  AVDT_CODEC_SIZE ; 
 int /*<<< orphan*/  BTC_MEDIA_AUDIO_SINK_CFG_UPDATE ; 
 int /*<<< orphan*/  btc_a2dp_sink_ctrl (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* osi_malloc (int) ; 

void btc_a2dp_sink_reset_decoder(UINT8 *p_av)
{
    APPL_TRACE_EVENT("btc reset decoder");
    APPL_TRACE_DEBUG("btc reset decoder p_codec_info[%x:%x:%x:%x:%x:%x]\n",
                     p_av[1], p_av[2], p_av[3],
                     p_av[4], p_av[5], p_av[6]);

    tBTC_MEDIA_SINK_CFG_UPDATE *p_buf;
    if (NULL == (p_buf = osi_malloc(sizeof(tBTC_MEDIA_SINK_CFG_UPDATE)))) {
        APPL_TRACE_ERROR("btc reset decoder No Buffer ");
        return;
    }

    memcpy(p_buf->codec_info, p_av, AVDT_CODEC_SIZE);
    btc_a2dp_sink_ctrl(BTC_MEDIA_AUDIO_SINK_CFG_UPDATE, p_buf);
}