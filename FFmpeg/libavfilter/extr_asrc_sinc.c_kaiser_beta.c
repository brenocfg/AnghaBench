#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ FF_ARRAY_ELEMS (float const**) ; 
 size_t av_clip (int,int /*<<< orphan*/ ,scalar_t__) ; 
 float logf (float) ; 
 float powf (float,float) ; 

__attribute__((used)) static float kaiser_beta(float att, float tr_bw)
{
    if (att >= 60.f) {
        static const float coefs[][4] = {
            {-6.784957e-10, 1.02856e-05, 0.1087556, -0.8988365 + .001},
            {-6.897885e-10, 1.027433e-05, 0.10876, -0.8994658 + .002},
            {-1.000683e-09, 1.030092e-05, 0.1087677, -0.9007898 + .003},
            {-3.654474e-10, 1.040631e-05, 0.1087085, -0.8977766 + .006},
            {8.106988e-09, 6.983091e-06, 0.1091387, -0.9172048 + .015},
            {9.519571e-09, 7.272678e-06, 0.1090068, -0.9140768 + .025},
            {-5.626821e-09, 1.342186e-05, 0.1083999, -0.9065452 + .05},
            {-9.965946e-08, 5.073548e-05, 0.1040967, -0.7672778 + .085},
            {1.604808e-07, -5.856462e-05, 0.1185998, -1.34824 + .1},
            {-1.511964e-07, 6.363034e-05, 0.1064627, -0.9876665 + .18},
        };
        float realm = logf(tr_bw / .0005f) / logf(2.f);
        float const *c0 = coefs[av_clip((int)realm, 0, FF_ARRAY_ELEMS(coefs) - 1)];
        float const *c1 = coefs[av_clip(1 + (int)realm, 0, FF_ARRAY_ELEMS(coefs) - 1)];
        float b0 = ((c0[0] * att + c0[1]) * att + c0[2]) * att + c0[3];
        float b1 = ((c1[0] * att + c1[1]) * att + c1[2]) * att + c1[3];

        return b0 + (b1 - b0) * (realm - (int)realm);
    }
    if (att > 50.f)
        return .1102f * (att - 8.7f);
    if (att > 20.96f)
        return .58417f * powf(att - 20.96f, .4f) + .07886f * (att - 20.96f);
    return 0;
}