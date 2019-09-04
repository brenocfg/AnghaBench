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
struct TYPE_4__ {scalar_t__ planar; int bps; int ch_count; int /*<<< orphan*/ * ch; } ;
typedef  TYPE_1__ AudioData ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void copy(AudioData *out, AudioData *in,
                 int count){
    av_assert0(out->planar == in->planar);
    av_assert0(out->bps == in->bps);
    av_assert0(out->ch_count == in->ch_count);
    if(out->planar){
        int ch;
        for(ch=0; ch<out->ch_count; ch++)
            memcpy(out->ch[ch], in->ch[ch], count*out->bps);
    }else
        memcpy(out->ch[0], in->ch[0], count*out->ch_count*out->bps);
}