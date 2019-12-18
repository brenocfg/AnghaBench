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
typedef  int /*<<< orphan*/  tBTA_HFP_PEER_CODEC ;
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
#define  SCO_STATE_OFF 131 
#define  SCO_STATE_OFF_TRANSFER 130 
#define  SCO_STATE_ON 129 
#define  SCO_STATE_SETUP 128 

void bta_hf_client_co_audio_state(UINT16 handle, UINT8 state, tBTA_HFP_PEER_CODEC codec)
{
    switch (state)
    {
    case SCO_STATE_ON:
    case SCO_STATE_OFF:
    case SCO_STATE_OFF_TRANSFER:
    case SCO_STATE_SETUP:
    default:
        break;
    }
}