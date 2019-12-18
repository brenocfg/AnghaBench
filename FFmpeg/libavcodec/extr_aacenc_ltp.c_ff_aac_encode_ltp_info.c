#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ profile; int /*<<< orphan*/  pb; } ;
struct TYPE_7__ {int /*<<< orphan*/ * used; int /*<<< orphan*/  coef_idx; int /*<<< orphan*/  lag; int /*<<< orphan*/  present; } ;
struct TYPE_9__ {TYPE_1__ ltp; int /*<<< orphan*/  max_sfb; int /*<<< orphan*/  predictor_present; } ;
struct TYPE_8__ {TYPE_3__ ics; } ;
typedef  TYPE_2__ SingleChannelElement ;
typedef  TYPE_3__ IndividualChannelStream ;
typedef  TYPE_4__ AACEncContext ;

/* Variables and functions */
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FF_PROFILE_AAC_LTP ; 
 int /*<<< orphan*/  MAX_LTP_LONG_SFB ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void ff_aac_encode_ltp_info(AACEncContext *s, SingleChannelElement *sce,
                            int common_window)
{
    int i;
    IndividualChannelStream *ics = &sce->ics;
    if (s->profile != FF_PROFILE_AAC_LTP || !ics->predictor_present)
        return;
    if (common_window)
        put_bits(&s->pb, 1, 0);
    put_bits(&s->pb, 1, ics->ltp.present);
    if (!ics->ltp.present)
        return;
    put_bits(&s->pb, 11, ics->ltp.lag);
    put_bits(&s->pb, 3,  ics->ltp.coef_idx);
    for (i = 0; i < FFMIN(ics->max_sfb, MAX_LTP_LONG_SFB); i++)
        put_bits(&s->pb, 1, ics->ltp.used[i]);
}