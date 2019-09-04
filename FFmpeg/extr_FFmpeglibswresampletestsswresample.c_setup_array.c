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
 int SWR_CH_MAX ; 
 int av_get_bytes_per_sample (int) ; 
 scalar_t__ av_sample_fmt_is_planar (int) ; 

__attribute__((used)) static void setup_array(uint8_t *out[SWR_CH_MAX], uint8_t *in, enum AVSampleFormat format, int samples){
    if(av_sample_fmt_is_planar(format)){
        int i;
        int plane_size= av_get_bytes_per_sample(format&0xFF)*samples;
        format&=0xFF;
        for(i=0; i<SWR_CH_MAX; i++){
            out[i]= in + i*plane_size;
        }
    }else{
        out[0]= in;
    }
}