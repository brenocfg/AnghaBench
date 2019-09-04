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
typedef  int int64_t ;
struct TYPE_6__ {int width; int height; } ;
struct TYPE_5__ {int den; int num; } ;
typedef  TYPE_1__ AVRational ;
typedef  TYPE_2__ AVCodecParameters ;

/* Variables and functions */

__attribute__((used)) static int get_vp9_level(AVCodecParameters *par, AVRational *frame_rate) {
    int picture_size = par->width * par->height;
    int64_t sample_rate;

    // All decisions will be based on picture_size, if frame rate is missing/invalid
    if (!frame_rate || !frame_rate->den)
        sample_rate = 0;
    else
        sample_rate = ((int64_t)picture_size * frame_rate->num) / frame_rate->den;

    if (picture_size <= 0) {
        return 0;
    } else if (sample_rate <= 829440     && picture_size <= 36864) {
        return 10;
    } else if (sample_rate <= 2764800    && picture_size <= 73728) {
        return 11;
    } else if (sample_rate <= 4608000    && picture_size <= 122880) {
        return 20;
    } else if (sample_rate <= 9216000    && picture_size <= 245760) {
        return 21;
    } else if (sample_rate <= 20736000   && picture_size <= 552960) {
        return 30;
    } else if (sample_rate <= 36864000   && picture_size <= 983040) {
        return 31;
    } else if (sample_rate <= 83558400   && picture_size <= 2228224) {
        return 40;
    } else if (sample_rate <= 160432128  && picture_size <= 2228224) {
        return 41;
    } else if (sample_rate <= 311951360  && picture_size <= 8912896) {
        return 50;
    } else if (sample_rate <= 588251136  && picture_size <= 8912896) {
        return 51;
    } else if (sample_rate <= 1176502272 && picture_size <= 8912896) {
        return 52;
    } else if (sample_rate <= 1176502272 && picture_size <= 35651584) {
        return 60;
    } else if (sample_rate <= 2353004544 && picture_size <= 35651584) {
        return 61;
    } else if (sample_rate <= 4706009088 && picture_size <= 35651584) {
        return 62;
    } else {
        return 0;
    }
}