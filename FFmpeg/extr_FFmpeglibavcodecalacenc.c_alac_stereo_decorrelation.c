#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_3__ {int** sample_buf; int frame_size; int interlacing_leftweight; int interlacing_shift; } ;
typedef  TYPE_1__ AlacEncodeContext ;

/* Variables and functions */
#define  ALAC_CHMODE_LEFT_RIGHT 130 
#define  ALAC_CHMODE_LEFT_SIDE 129 
#define  ALAC_CHMODE_RIGHT_SIDE 128 
 int estimate_stereo_mode (int*,int*,int) ; 

__attribute__((used)) static void alac_stereo_decorrelation(AlacEncodeContext *s)
{
    int32_t *left = s->sample_buf[0], *right = s->sample_buf[1];
    int i, mode, n = s->frame_size;
    int32_t tmp;

    mode = estimate_stereo_mode(left, right, n);

    switch (mode) {
    case ALAC_CHMODE_LEFT_RIGHT:
        s->interlacing_leftweight = 0;
        s->interlacing_shift      = 0;
        break;
    case ALAC_CHMODE_LEFT_SIDE:
        for (i = 0; i < n; i++)
            right[i] = left[i] - right[i];
        s->interlacing_leftweight = 1;
        s->interlacing_shift      = 0;
        break;
    case ALAC_CHMODE_RIGHT_SIDE:
        for (i = 0; i < n; i++) {
            tmp = right[i];
            right[i] = left[i] - right[i];
            left[i]  = tmp + (right[i] >> 31);
        }
        s->interlacing_leftweight = 1;
        s->interlacing_shift      = 31;
        break;
    default:
        for (i = 0; i < n; i++) {
            tmp = left[i];
            left[i]  = (tmp + right[i]) >> 1;
            right[i] =  tmp - right[i];
        }
        s->interlacing_leftweight = 1;
        s->interlacing_shift      = 1;
        break;
    }
}