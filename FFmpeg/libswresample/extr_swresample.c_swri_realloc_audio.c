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
struct TYPE_3__ {int bps; int ch_count; int count; int /*<<< orphan*/  data; scalar_t__* ch; scalar_t__ planar; } ;
typedef  TYPE_1__ AudioData ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int,int /*<<< orphan*/ ) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_mallocz_array (int,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 

int swri_realloc_audio(AudioData *a, int count){
    int i, countb;
    AudioData old;

    if(count < 0 || count > INT_MAX/2/a->bps/a->ch_count)
        return AVERROR(EINVAL);

    if(a->count >= count)
        return 0;

    count*=2;

    countb= FFALIGN(count*a->bps, ALIGN);
    old= *a;

    av_assert0(a->bps);
    av_assert0(a->ch_count);

    a->data= av_mallocz_array(countb, a->ch_count);
    if(!a->data)
        return AVERROR(ENOMEM);
    for(i=0; i<a->ch_count; i++){
        a->ch[i]= a->data + i*(a->planar ? countb : a->bps);
        if(a->count && a->planar) memcpy(a->ch[i], old.ch[i], a->count*a->bps);
    }
    if(a->count && !a->planar) memcpy(a->ch[0], old.ch[0], a->count*a->ch_count*a->bps);
    av_freep(&old.data);
    a->count= count;

    return 1;
}