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
struct TYPE_5__ {int n; TYPE_1__* vi; int /*<<< orphan*/  bark; } ;
typedef  TYPE_2__ vorbis_look_psy ;
struct TYPE_4__ {int noisewindowfixed; float* noisecompand; } ;

/* Variables and functions */
 int NOISE_COMPAND_LEVELS ; 
 int /*<<< orphan*/  _analysis_output (char*,int,float*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float* alloca (int) ; 
 int /*<<< orphan*/  bark_noise_hybridmp (int,int /*<<< orphan*/ ,float*,float*,int,int) ; 

void _vp_noisemask(vorbis_look_psy *p,
                   float *logmdct,
                   float *logmask){

  int i,n=p->n;
  float *work=alloca(n*sizeof(*work));

  bark_noise_hybridmp(n,p->bark,logmdct,logmask,
                      140.,-1);

  for(i=0;i<n;i++)work[i]=logmdct[i]-logmask[i];

  bark_noise_hybridmp(n,p->bark,work,logmask,0.,
                      p->vi->noisewindowfixed);

  for(i=0;i<n;i++)work[i]=logmdct[i]-work[i];

#if 0
  {
    static int seq=0;

    float work2[n];
    for(i=0;i<n;i++){
      work2[i]=logmask[i]+work[i];
    }

    if(seq&1)
      _analysis_output("median2R",seq/2,work,n,1,0,0);
    else
      _analysis_output("median2L",seq/2,work,n,1,0,0);

    if(seq&1)
      _analysis_output("envelope2R",seq/2,work2,n,1,0,0);
    else
      _analysis_output("envelope2L",seq/2,work2,n,1,0,0);
    seq++;
  }
#endif

  for(i=0;i<n;i++){
    int dB=logmask[i]+.5;
    if(dB>=NOISE_COMPAND_LEVELS)dB=NOISE_COMPAND_LEVELS-1;
    if(dB<0)dB=0;
    logmask[i]= work[i]+p->vi->noisecompand[dB];
  }

}