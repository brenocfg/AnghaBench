#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/ * inputs; TYPE_5__* priv; } ;
struct TYPE_24__ {TYPE_8__* src; } ;
struct TYPE_23__ {scalar_t__ score; scalar_t__ whole; int /*<<< orphan*/  matchframes; TYPE_2__* second; TYPE_1__* first; } ;
struct TYPE_22__ {int nb_inputs; scalar_t__ mode; TYPE_4__* streamcontexts; int /*<<< orphan*/  filename; } ;
struct TYPE_20__ {double num; double den; } ;
struct TYPE_21__ {int exported; TYPE_3__ time_base; } ;
struct TYPE_19__ {scalar_t__ pts; } ;
struct TYPE_18__ {scalar_t__ pts; } ;
typedef  TYPE_4__ StreamContext ;
typedef  TYPE_5__ SignatureContext ;
typedef  TYPE_6__ MatchingInfo ;
typedef  TYPE_7__ AVFilterLink ;
typedef  TYPE_8__ AVFilterContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 scalar_t__ MODE_OFF ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ export (TYPE_8__*,TYPE_4__*,int) ; 
 int ff_request_frame (int /*<<< orphan*/ ) ; 
 TYPE_6__ lookup_signatures (TYPE_8__*,TYPE_5__*,TYPE_4__*,TYPE_4__*,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int request_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    SignatureContext *sic = ctx->priv;
    StreamContext *sc, *sc2;
    MatchingInfo match;
    int i, j, ret;
    int lookup = 1; /* indicates wheather EOF of all files is reached */

    /* process all inputs */
    for (i = 0; i < sic->nb_inputs; i++){
        sc = &(sic->streamcontexts[i]);

        ret = ff_request_frame(ctx->inputs[i]);

        /* return if unexpected error occurs in input stream */
        if (ret < 0 && ret != AVERROR_EOF)
            return ret;

        /* export signature at EOF */
        if (ret == AVERROR_EOF && !sc->exported) {
            /* export if wanted */
            if (strlen(sic->filename) > 0) {
                if (export(ctx, sc, i) < 0)
                    return ret;
            }
            sc->exported = 1;
        }
        lookup &= sc->exported;
    }

    /* signature lookup */
    if (lookup && sic->mode != MODE_OFF) {
        /* iterate over every pair */
        for (i = 0; i < sic->nb_inputs; i++) {
            sc = &(sic->streamcontexts[i]);
            for (j = i+1; j < sic->nb_inputs; j++) {
                sc2 = &(sic->streamcontexts[j]);
                match = lookup_signatures(ctx, sic, sc, sc2, sic->mode);
                if (match.score != 0) {
                    av_log(ctx, AV_LOG_INFO, "matching of video %d at %f and %d at %f, %d frames matching\n",
                            i, ((double) match.first->pts * sc->time_base.num) / sc->time_base.den,
                            j, ((double) match.second->pts * sc2->time_base.num) / sc2->time_base.den,
                            match.matchframes);
                    if (match.whole)
                        av_log(ctx, AV_LOG_INFO, "whole video matching\n");
                } else {
                    av_log(ctx, AV_LOG_INFO, "no matching of video %d and %d\n", i, j);
                }
            }
        }
    }

    return ret;
}