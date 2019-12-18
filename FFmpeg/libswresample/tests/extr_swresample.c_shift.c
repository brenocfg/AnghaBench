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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;

/* Variables and functions */
 int av_get_alt_sample_fmt (int,int /*<<< orphan*/ ) ; 
 int av_get_bytes_per_sample (int) ; 
 scalar_t__ av_sample_fmt_is_planar (int) ; 

__attribute__((used)) static void shift(uint8_t *a[], int index, int ch_count, enum AVSampleFormat f){
    int ch;

    if(av_sample_fmt_is_planar(f)){
        f= av_get_alt_sample_fmt(f, 0);
        for(ch= 0; ch<ch_count; ch++)
            a[ch] += index*av_get_bytes_per_sample(f);
    }else{
        a[0] += index*ch_count*av_get_bytes_per_sample(f);
    }
}