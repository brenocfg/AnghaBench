#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int confidence; int /*<<< orphan*/  framesig; } ;
struct TYPE_12__ {double meandist; int matchframes; int whole; struct TYPE_12__* next; TYPE_3__* second; TYPE_3__* first; int /*<<< orphan*/  offset; int /*<<< orphan*/  score; int /*<<< orphan*/  framerateratio; } ;
struct TYPE_11__ {int thl1; int thdi; double thit; } ;
typedef  TYPE_1__ SignatureContext ;
typedef  TYPE_2__ MatchingInfo ;
typedef  TYPE_3__ FineSignature ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int DIR_NEXT ; 
 int DIR_NEXT_END ; 
 int DIR_PREV ; 
 int DIR_PREV_END ; 
 double FFMAX (int,int) ; 
 int MODE_FAST ; 
 int STATUS_BEGIN_REACHED ; 
 int STATUS_END_REACHED ; 
 int STATUS_NULL ; 
 int get_l1dist (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iterate_frame (int /*<<< orphan*/ ,TYPE_3__**,TYPE_3__**,int,int*,int) ; 

__attribute__((used)) static MatchingInfo evaluate_parameters(AVFilterContext *ctx, SignatureContext *sc, MatchingInfo *infos, MatchingInfo bestmatch, int mode)
{
    int dist, distsum = 0, bcount = 1, dir = DIR_NEXT;
    int fcount = 0, goodfcount = 0, gooda = 0, goodb = 0;
    double meandist, minmeandist = bestmatch.meandist;
    int tolerancecount = 0;
    FineSignature *a, *b, *aprev, *bprev;
    int status = STATUS_NULL;

    for (; infos != NULL; infos = infos->next) {
        a = infos->first;
        b = infos->second;
        while (1) {
            dist = get_l1dist(ctx, sc, a->framesig, b->framesig);

            if (dist > sc->thl1) {
                if (a->confidence >= 1 || b->confidence >= 1) {
                    /* bad frame (because high different information) */
                    tolerancecount++;
                }

                if (tolerancecount > 2) {
                    a = aprev;
                    b = bprev;
                    if (dir == DIR_NEXT) {
                        /* turn around */
                        a = infos->first;
                        b = infos->second;
                        dir = DIR_PREV;
                    } else {
                        break;
                    }
                }
            } else {
                /* good frame */
                distsum += dist;
                goodfcount++;
                tolerancecount=0;

                aprev = a;
                bprev = b;

                if (a->confidence < 1) gooda++;
                if (b->confidence < 1) goodb++;
            }

            fcount++;

            dir = iterate_frame(infos->framerateratio, &a, &b, fcount, &bcount, dir);
            if (dir == DIR_NEXT_END) {
                status = STATUS_END_REACHED;
                a = infos->first;
                b = infos->second;
                dir = iterate_frame(infos->framerateratio, &a, &b, fcount, &bcount, DIR_PREV);
            }

            if (dir == DIR_PREV_END) {
                status |= STATUS_BEGIN_REACHED;
                break;
            }

            if (sc->thdi != 0 && bcount >= sc->thdi) {
                break; /* enough frames found */
            }
        }

        if (bcount < sc->thdi)
            continue; /* matching sequence is too short */
        if ((double) goodfcount / (double) fcount < sc->thit)
            continue;
        if ((double) goodfcount*0.5 < FFMAX(gooda, goodb))
            continue;

        meandist = (double) goodfcount / (double) distsum;

        if (meandist < minmeandist ||
                status == STATUS_END_REACHED | STATUS_BEGIN_REACHED ||
                mode == MODE_FAST){
            minmeandist = meandist;
            /* bestcandidate in this iteration */
            bestmatch.meandist = meandist;
            bestmatch.matchframes = bcount;
            bestmatch.framerateratio = infos->framerateratio;
            bestmatch.score = infos->score;
            bestmatch.offset = infos->offset;
            bestmatch.first = infos->first;
            bestmatch.second = infos->second;
            bestmatch.whole = 0; /* will be set to true later */
            bestmatch.next = NULL;
        }

        /* whole sequence is automatically best match */
        if (status == (STATUS_END_REACHED | STATUS_BEGIN_REACHED)) {
            bestmatch.whole = 1;
            break;
        }

        /* first matching sequence is enough, finding the best one is not necessary */
        if (mode == MODE_FAST) {
            break;
        }
    }
    return bestmatch;
}