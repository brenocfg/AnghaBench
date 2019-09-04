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
struct TYPE_6__ {int* scalefactors; size_t q_unit_cnt; int* codebookset; } ;
struct TYPE_5__ {int samplerate_idx; } ;
typedef  TYPE_1__ ATRAC9Context ;
typedef  TYPE_2__ ATRAC9ChannelData ;
typedef  int /*<<< orphan*/  ATRAC9BlockData ;

/* Variables and functions */
 int FFMIN (int const,int const) ; 
 int* at9_q_unit_to_coeff_cnt ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void calc_codebook_idx(ATRAC9Context *s, ATRAC9BlockData *b,
                                     ATRAC9ChannelData *c)
{
    int avg = 0;
    const int last_sf = c->scalefactors[c->q_unit_cnt];

    memset(c->codebookset, 0, sizeof(c->codebookset));

    if (c->q_unit_cnt <= 1)
        return;
    if (s->samplerate_idx > 7)
        return;

    c->scalefactors[c->q_unit_cnt] = c->scalefactors[c->q_unit_cnt - 1];

    if (c->q_unit_cnt > 12) {
        for (int i = 0; i < 12; i++)
            avg += c->scalefactors[i];
        avg = (avg + 6) / 12;
    }

    for (int i = 8; i < c->q_unit_cnt; i++) {
        const int prev = c->scalefactors[i - 1];
        const int cur  = c->scalefactors[i    ];
        const int next = c->scalefactors[i + 1];
        const int min  = FFMIN(prev, next);
        if ((cur - min >= 3 || 2*cur - prev - next >= 3))
            c->codebookset[i] = 1;
    }


    for (int i = 12; i < c->q_unit_cnt; i++) {
        const int cur = c->scalefactors[i];
        const int cnd = at9_q_unit_to_coeff_cnt[i] == 16;
        const int min = FFMIN(c->scalefactors[i + 1], c->scalefactors[i - 1]);
        if (c->codebookset[i])
            continue;

        c->codebookset[i] = (((cur - min) >= 2) && (cur >= (avg - cnd)));
    }

    c->scalefactors[c->q_unit_cnt] = last_sf;
}