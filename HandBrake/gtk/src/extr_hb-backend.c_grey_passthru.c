#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_2__ signal_user_data_t ;
struct TYPE_11__ {int codec; } ;
typedef  TYPE_3__ hb_encoder_t ;
struct TYPE_9__ {int codec; } ;
struct TYPE_12__ {TYPE_1__ in; } ;
typedef  TYPE_4__ hb_audio_config_t ;

/* Variables and functions */
 int HB_ACODEC_MASK ; 
 int HB_ACODEC_PASS_FLAG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  grey_builder_combo_box_item (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* hb_audio_encoder_get_next (TYPE_3__ const*) ; 

__attribute__((used)) static void grey_passthru(signal_user_data_t *ud, hb_audio_config_t *aconfig)
{
    const hb_encoder_t *enc;

    if (aconfig == NULL)
        return;

    for (enc = hb_audio_encoder_get_next(NULL); enc != NULL;
         enc = hb_audio_encoder_get_next(enc))
    {
        if (!(enc->codec & HB_ACODEC_PASS_FLAG))
            continue;
        if ((enc->codec & HB_ACODEC_MASK) !=
            (aconfig->in.codec & HB_ACODEC_MASK))
        {
            grey_builder_combo_box_item(ud->builder, "AudioEncoder",
                enc->codec, TRUE);
        }
    }
}