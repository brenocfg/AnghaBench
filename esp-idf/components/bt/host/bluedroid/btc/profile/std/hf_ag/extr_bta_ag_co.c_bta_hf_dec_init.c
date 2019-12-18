#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  decoder_context_data; int /*<<< orphan*/  decoder_context; } ;
struct TYPE_3__ {int /*<<< orphan*/  plc_state; } ;
typedef  int /*<<< orphan*/  OI_UINT32 ;
typedef  int /*<<< orphan*/  OI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int HF_SBC_DEC_CONTEXT_DATA_LEN ; 
 int /*<<< orphan*/  OI_CODEC_SBC_DecoderReset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ bta_ag_co_cb ; 
 TYPE_1__ bta_hf_ct_plc ; 
 int /*<<< orphan*/  sbc_plc_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bta_hf_dec_init(void) 
{
#if (PLC_INCLUDED == TRUE)
    sbc_plc_init(&(bta_hf_ct_plc.plc_state));
#endif  ///(PLC_INCLUDED == TRUE)

    OI_STATUS status = OI_CODEC_SBC_DecoderReset(&bta_ag_co_cb.decoder_context, bta_ag_co_cb.decoder_context_data,
                                       HF_SBC_DEC_CONTEXT_DATA_LEN * sizeof(OI_UINT32), 1, 1, FALSE, TRUE);
    if (!OI_SUCCESS(status)) {
        APPL_TRACE_ERROR("OI_CODEC_SBC_DecoderReset failed with error code %d\n", status);
    }
}