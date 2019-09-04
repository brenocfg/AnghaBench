#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ch_count; scalar_t__* ch; } ;
struct TYPE_7__ {int filter_length; scalar_t__ index; int felem_size; scalar_t__ phase_count; } ;
typedef  TYPE_1__ ResampleContext ;
typedef  TYPE_2__ AudioData ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int swri_realloc_audio (TYPE_2__*,int) ; 

__attribute__((used)) static int invert_initial_buffer(ResampleContext *c, AudioData *dst, const AudioData *src,
                                 int in_count, int *out_idx, int *out_sz)
{
    int n, ch, num = FFMIN(in_count + *out_sz, c->filter_length + 1), res;

    if (c->index >= 0)
        return 0;

    if ((res = swri_realloc_audio(dst, c->filter_length * 2 + 1)) < 0)
        return res;

    // copy
    for (n = *out_sz; n < num; n++) {
        for (ch = 0; ch < src->ch_count; ch++) {
            memcpy(dst->ch[ch] + ((c->filter_length + n) * c->felem_size),
                   src->ch[ch] + ((n - *out_sz) * c->felem_size), c->felem_size);
        }
    }

    // if not enough data is in, return and wait for more
    if (num < c->filter_length + 1) {
        *out_sz = num;
        *out_idx = c->filter_length;
        return INT_MAX;
    }

    // else invert
    for (n = 1; n <= c->filter_length; n++) {
        for (ch = 0; ch < src->ch_count; ch++) {
            memcpy(dst->ch[ch] + ((c->filter_length - n) * c->felem_size),
                   dst->ch[ch] + ((c->filter_length + n) * c->felem_size),
                   c->felem_size);
        }
    }

    res = num - *out_sz;
    *out_idx = c->filter_length;
    while (c->index < 0) {
        --*out_idx;
        c->index += c->phase_count;
    }
    *out_sz = FFMAX(*out_sz + c->filter_length,
                    1 + c->filter_length * 2) - *out_idx;

    return FFMAX(res, 0);
}