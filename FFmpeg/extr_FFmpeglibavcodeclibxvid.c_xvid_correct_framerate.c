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
struct TYPE_5__ {int den; int num; } ;
struct TYPE_6__ {TYPE_1__ time_base; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int av_gcd (int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,float,float) ; 
 double roundf (float) ; 

__attribute__((used)) static void xvid_correct_framerate(AVCodecContext *avctx)
{
    int frate, fbase;
    int est_frate, est_fbase;
    int gcd;
    float est_fps, fps;

    frate = avctx->time_base.den;
    fbase = avctx->time_base.num;

    gcd = av_gcd(frate, fbase);
    if (gcd > 1) {
        frate /= gcd;
        fbase /= gcd;
    }

    if (frate <= 65000 && fbase <= 65000) {
        avctx->time_base.den = frate;
        avctx->time_base.num = fbase;
        return;
    }

    fps     = (float) frate / (float) fbase;
    est_fps = roundf(fps * 1000.0) / 1000.0;

    est_frate = (int) est_fps;
    if (est_fps > (int) est_fps) {
        est_frate = (est_frate + 1) * 1000;
        est_fbase = (int) roundf((float) est_frate / est_fps);
    } else
        est_fbase = 1;

    gcd = av_gcd(est_frate, est_fbase);
    if (gcd > 1) {
        est_frate /= gcd;
        est_fbase /= gcd;
    }

    if (fbase > est_fbase) {
        avctx->time_base.den = est_frate;
        avctx->time_base.num = est_fbase;
        av_log(avctx, AV_LOG_DEBUG,
               "Xvid: framerate re-estimated: %.2f, %.3f%% correction\n",
               est_fps, (((est_fps - fps) / fps) * 100.0));
    } else {
        avctx->time_base.den = frate;
        avctx->time_base.num = fbase;
    }
}