#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t samplerate_index; scalar_t__ profile; int /*<<< orphan*/  pb; } ;
struct TYPE_7__ {int predictor_reset_group; int* prediction_used; int /*<<< orphan*/  predictor_present; int /*<<< orphan*/  max_sfb; } ;
struct TYPE_6__ {TYPE_2__ ics; } ;
typedef  TYPE_1__ SingleChannelElement ;
typedef  TYPE_2__ IndividualChannelStream ;
typedef  TYPE_3__ AACEncContext ;

/* Variables and functions */
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FF_PROFILE_AAC_MAIN ; 
 int /*<<< orphan*/ * ff_aac_pred_sfb_max ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

void ff_aac_encode_main_pred(AACEncContext *s, SingleChannelElement *sce)
{
    int sfb;
    IndividualChannelStream *ics = &sce->ics;
    const int pmax = FFMIN(ics->max_sfb, ff_aac_pred_sfb_max[s->samplerate_index]);

    if (s->profile != FF_PROFILE_AAC_MAIN ||
        !ics->predictor_present)
        return;

    put_bits(&s->pb, 1, !!ics->predictor_reset_group);
    if (ics->predictor_reset_group)
        put_bits(&s->pb, 5, ics->predictor_reset_group);
    for (sfb = 0; sfb < pmax; sfb++)
        put_bits(&s->pb, 1, ics->prediction_used[sfb]);
}