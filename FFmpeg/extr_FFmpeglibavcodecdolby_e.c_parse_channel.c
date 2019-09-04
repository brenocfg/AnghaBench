#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_15__ {int gr_code; int bw_code; int nb_groups; int nb_mstr_exp; TYPE_12__* groups; } ;
struct TYPE_14__ {int* rev_id; size_t prog_conf; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; TYPE_2__** channels; } ;
struct TYPE_13__ {int nb_exponent; int* nb_bias_exp; } ;
typedef  TYPE_1__ DBEContext ;
typedef  TYPE_2__ DBEChannel ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_12__*** frm_ofs_tab ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 int* lfe_channel_tab ; 
 int* nb_groups_tab ; 
 int* nb_mstr_exp_tab ; 
 int parse_bit_alloc (TYPE_1__*,TYPE_2__*) ; 
 int parse_exponents (TYPE_1__*,TYPE_2__*) ; 
 int parse_indices (TYPE_1__*,TYPE_2__*) ; 
 int parse_mantissas (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int parse_channel(DBEContext *s, int ch, int seg_id)
{
    DBEChannel *c = &s->channels[seg_id][ch];
    int i, ret;

    if (s->rev_id[ch] > 1) {
        avpriv_report_missing_feature(s->avctx, "Encoder revision %d", s->rev_id[ch]);
        return AVERROR_PATCHWELCOME;
    }

    if (ch == lfe_channel_tab[s->prog_conf]) {
        c->gr_code = 3;
        c->bw_code = 29;
    } else {
        c->gr_code = get_bits(&s->gb, 2);
        c->bw_code = get_bits(&s->gb, 3);
        if (c->gr_code == 3) {
            av_log(s->avctx, AV_LOG_ERROR, "Invalid group type code\n");
            return AVERROR_INVALIDDATA;
        }
    }

    c->nb_groups   = nb_groups_tab[c->gr_code];
    c->nb_mstr_exp = nb_mstr_exp_tab[c->gr_code];

    for (i = 0; i < c->nb_groups; i++) {
        c->groups[i] = frm_ofs_tab[seg_id][c->gr_code][i];
        if (c->nb_mstr_exp == 2) {
            c->groups[i].nb_exponent    -= c->bw_code;
            c->groups[i].nb_bias_exp[1] -= c->bw_code;
        }
    }

    if ((ret = parse_exponents(s, c)) < 0)
        return ret;
    if ((ret = parse_bit_alloc(s, c)) < 0)
        return ret;
    if ((ret = parse_indices(s, c)) < 0)
        return ret;
    if ((ret = parse_mantissas(s, c)) < 0)
        return ret;

    if (get_bits_left(&s->gb) < 0) {
        av_log(s->avctx, AV_LOG_ERROR, "Read past end of channel %d\n", ch);
        return AVERROR_INVALIDDATA;
    }

    return 0;
}