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
struct TYPE_4__ {int sco_codec; scalar_t__ codec_fallback; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*,int) ; 
#define  BTA_AG_CODEC_CVSD 130 
#define  BTA_AG_CODEC_MSBC 129 
#define  BTA_AG_CODEC_NONE 128 
 int /*<<< orphan*/  BTA_AG_RES_BCS ; 
 int /*<<< orphan*/  UUID_CODEC_CVSD ; 
 int /*<<< orphan*/  UUID_CODEC_MSBC ; 
 int /*<<< orphan*/  bta_ag_send_result (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bta_ag_send_bcs(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    UINT16 codec_uuid;

    if (p_scb->codec_fallback) {
        codec_uuid = UUID_CODEC_CVSD;
    } else {
        switch(p_scb->sco_codec) {
            case BTA_AG_CODEC_NONE:
                codec_uuid = UUID_CODEC_CVSD;
                break;
            
            case BTA_AG_CODEC_CVSD:
                codec_uuid = UUID_CODEC_CVSD;
                break;
            
            case BTA_AG_CODEC_MSBC:
                codec_uuid = UUID_CODEC_MSBC;
                break;
            
            default:
                APPL_TRACE_ERROR("bta_ag_send_bcs: unknown codec %d, use CVSD", p_scb->sco_codec);
                codec_uuid = UUID_CODEC_CVSD;
                break;
        }
    }
    /* send +BCS */
    APPL_TRACE_DEBUG("send +BCS codec is %d", codec_uuid);
    bta_ag_send_result(p_scb, BTA_AG_RES_BCS, NULL, codec_uuid);
}