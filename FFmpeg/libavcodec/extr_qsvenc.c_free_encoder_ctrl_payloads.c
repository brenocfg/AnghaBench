#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int NumPayload; int /*<<< orphan*/ * Payload; } ;
typedef  TYPE_1__ mfxEncodeCtrl ;

/* Variables and functions */
 int QSV_MAX_ENC_PAYLOAD ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_encoder_ctrl_payloads(mfxEncodeCtrl* enc_ctrl)
{
    if (enc_ctrl) {
        int i;
        for (i = 0; i < enc_ctrl->NumPayload && i < QSV_MAX_ENC_PAYLOAD; i++) {
            av_free(enc_ctrl->Payload[i]);
        }
        enc_ctrl->NumPayload = 0;
    }
}