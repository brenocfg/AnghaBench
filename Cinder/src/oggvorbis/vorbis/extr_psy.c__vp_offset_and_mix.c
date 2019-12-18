#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int n; float m_val; float** noiseoffset; TYPE_1__* vi; } ;
typedef  TYPE_2__ vorbis_look_psy ;
struct TYPE_4__ {float* tone_masteratt; float noisemaxsupp; } ;

/* Variables and functions */
 float max (float,float) ; 

void _vp_offset_and_mix(vorbis_look_psy *p,
                        float *noise,
                        float *tone,
                        int offset_select,
                        float *logmask,
                        float *mdct,
                        float *logmdct){
  int i,n=p->n;
  float de, coeffi, cx;/* AoTuV */
  float toneatt=p->vi->tone_masteratt[offset_select];

  cx = p->m_val;

  for(i=0;i<n;i++){
    float val= noise[i]+p->noiseoffset[offset_select][i];
    if(val>p->vi->noisemaxsupp)val=p->vi->noisemaxsupp;
    logmask[i]=max(val,tone[i]+toneatt);


    /* AoTuV */
    /** @ M1 **
        The following codes improve a noise problem.
        A fundamental idea uses the value of masking and carries out
        the relative compensation of the MDCT.
        However, this code is not perfect and all noise problems cannot be solved.
        by Aoyumi @ 2004/04/18
    */

    if(offset_select == 1) {
      coeffi = -17.2;       /* coeffi is a -17.2dB threshold */
      val = val - logmdct[i];  /* val == mdct line value relative to floor in dB */

      if(val > coeffi){
        /* mdct value is > -17.2 dB below floor */

        de = 1.0-((val-coeffi)*0.005*cx);
        /* pro-rated attenuation:
           -0.00 dB boost if mdct value is -17.2dB (relative to floor)
           -0.77 dB boost if mdct value is 0dB (relative to floor)
           -1.64 dB boost if mdct value is +17.2dB (relative to floor)
           etc... */

        if(de < 0) de = 0.0001;
      }else
        /* mdct value is <= -17.2 dB below floor */

        de = 1.0-((val-coeffi)*0.0003*cx);
      /* pro-rated attenuation:
         +0.00 dB atten if mdct value is -17.2dB (relative to floor)
         +0.45 dB atten if mdct value is -34.4dB (relative to floor)
         etc... */

      mdct[i] *= de;

    }
  }
}