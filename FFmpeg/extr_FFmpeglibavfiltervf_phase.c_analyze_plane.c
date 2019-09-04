#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum PhaseMode { ____Placeholder_PhaseMode } PhaseMode ;
struct TYPE_4__ {int* linesize; int height; int width; int /*<<< orphan*/ ** data; scalar_t__ top_field_first; scalar_t__ interlaced_frame; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
#define  ANALYZE 131 
 int AUTO ; 
 int AUTO_ANALYZE ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int BOTTOM_FIRST ; 
#define  BOTTOM_FIRST_ANALYZE 130 
 int DIFF (int /*<<< orphan*/  const*,int const,int /*<<< orphan*/  const*,int const) ; 
#define  FULL_ANALYZE 129 
 int PROGRESSIVE ; 
 int TOP_FIRST ; 
#define  TOP_FIRST_ANALYZE 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char,double,double,double) ; 

__attribute__((used)) static enum PhaseMode analyze_plane(void *ctx, enum PhaseMode mode, AVFrame *old, AVFrame *new)
{
    double bdiff, tdiff, pdiff;

    if (mode == AUTO) {
        mode = new->interlaced_frame ? new->top_field_first ?
               TOP_FIRST : BOTTOM_FIRST : PROGRESSIVE;
    } else if (mode == AUTO_ANALYZE) {
        mode = new->interlaced_frame ? new->top_field_first ?
               TOP_FIRST_ANALYZE : BOTTOM_FIRST_ANALYZE : FULL_ANALYZE;
    }

    if (mode <= BOTTOM_FIRST) {
        bdiff = pdiff = tdiff = 65536.0;
    } else {
        const int ns = new->linesize[0];
        const int os = old->linesize[0];
        const uint8_t *nptr = new->data[0];
        const uint8_t *optr = old->data[0];
        const int h = new->height;
        const int w = new->width;
        int bdif, tdif, pdif;
        double scale;

        int top = 0, t;
        const uint8_t *rend, *end = nptr + (h - 2) * ns;

        bdiff = pdiff = tdiff = 0.0;

        nptr += ns;
        optr += os;
        while (nptr < end) {
            pdif = tdif = bdif = 0;

            switch (mode) {
            case TOP_FIRST_ANALYZE:
                if (top) {
                    for (rend = nptr + w; nptr < rend; nptr++, optr++) {
                        pdif += DIFF(nptr, ns, nptr, ns);
                        tdif += DIFF(nptr, ns, optr, os);
                    }
                } else {
                    for (rend = nptr + w; nptr < rend; nptr++, optr++) {
                        pdif += DIFF(nptr, ns, nptr, ns);
                        tdif += DIFF(optr, os, nptr, ns);
                    }
                }
                break;
            case BOTTOM_FIRST_ANALYZE:
                if (top) {
                    for (rend = nptr + w; nptr < rend; nptr++, optr++) {
                        pdif += DIFF(nptr, ns, nptr, ns);
                        bdif += DIFF(optr, os, nptr, ns);
                    }
                } else {
                    for (rend = nptr + w; nptr < rend; nptr++, optr++) {
                        pdif += DIFF(nptr, ns, nptr, ns);
                        bdif += DIFF(nptr, ns, optr, os);
                    }
                }
                break;
            case ANALYZE:
                if (top) {
                    for (rend = nptr + w; nptr < rend; nptr++, optr++) {
                        tdif += DIFF(nptr, ns, optr, os);
                        bdif += DIFF(optr, os, nptr, ns);
                    }
                } else {
                    for (rend = nptr + w; nptr < rend; nptr++, optr++) {
                        bdif += DIFF(nptr, ns, optr, os);
                        tdif += DIFF(optr, os, nptr, ns);
                    }
                }
                break;
            case FULL_ANALYZE:
                if (top) {
                    for (rend = nptr + w; nptr < rend; nptr++, optr++) {
                        pdif += DIFF(nptr, ns, nptr, ns);
                        tdif += DIFF(nptr, ns, optr, os);
                        bdif += DIFF(optr, os, nptr, ns);
                    }
                } else {
                    for (rend = nptr + w; nptr < rend; nptr++, optr++) {
                        pdif += DIFF(nptr, ns, nptr, ns);
                        bdif += DIFF(nptr, ns, optr, os);
                        tdif += DIFF(optr, os, nptr, ns);
                    }
                }
                break;
            default:
                av_assert0(0);
            }

            pdiff += (double)pdif;
            tdiff += (double)tdif;
            bdiff += (double)bdif;
            nptr += ns - w;
            optr += os - w;
            top ^= 1;
        }

        scale = 1.0 / (w * (h - 3)) / 25.0;
        pdiff *= scale;
        tdiff *= scale;
        bdiff *= scale;

        if (mode == TOP_FIRST_ANALYZE) {
            bdiff = 65536.0;
        } else if (mode == BOTTOM_FIRST_ANALYZE) {
            tdiff = 65536.0;
        } else if (mode == ANALYZE) {
            pdiff = 65536.0;
        }

        if (bdiff < pdiff && bdiff < tdiff) {
            mode = BOTTOM_FIRST;
        } else if (tdiff < pdiff && tdiff < bdiff) {
            mode = TOP_FIRST;
        } else {
            mode = PROGRESSIVE;
        }
    }

    av_log(ctx, AV_LOG_DEBUG, "mode=%c tdiff=%f bdiff=%f pdiff=%f\n",
           mode == BOTTOM_FIRST ? 'b' : mode == TOP_FIRST ? 't' : 'p',
           tdiff, bdiff, pdiff);
    return mode;
}