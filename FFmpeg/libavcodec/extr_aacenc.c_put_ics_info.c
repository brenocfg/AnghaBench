#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pb; } ;
struct TYPE_5__ {int* window_sequence; int* use_kb_window; int max_sfb; int /*<<< orphan*/ * group_len; int /*<<< orphan*/  predictor_present; } ;
typedef  TYPE_1__ IndividualChannelStream ;
typedef  TYPE_2__ AACEncContext ;

/* Variables and functions */
 scalar_t__ EIGHT_SHORT_SEQUENCE ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void put_ics_info(AACEncContext *s, IndividualChannelStream *info)
{
    int w;

    put_bits(&s->pb, 1, 0);                // ics_reserved bit
    put_bits(&s->pb, 2, info->window_sequence[0]);
    put_bits(&s->pb, 1, info->use_kb_window[0]);
    if (info->window_sequence[0] != EIGHT_SHORT_SEQUENCE) {
        put_bits(&s->pb, 6, info->max_sfb);
        put_bits(&s->pb, 1, !!info->predictor_present);
    } else {
        put_bits(&s->pb, 4, info->max_sfb);
        for (w = 1; w < 8; w++)
            put_bits(&s->pb, 1, !info->group_len[w]);
    }
}