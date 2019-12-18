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
struct TYPE_4__ {TYPE_2__* vi; } ;
typedef  TYPE_1__ vorbis_look_psy ;
struct TYPE_5__ {int normal_start; float normal_thresh; scalar_t__ normal_p; } ;
typedef  TYPE_2__ vorbis_info_psy ;

/* Variables and functions */
 float** alloca (int) ; 
 int /*<<< orphan*/  apsort ; 
 int /*<<< orphan*/  qsort (float**,int,int,int /*<<< orphan*/ ) ; 
 int rint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqrt (float) ; 
 int unitnorm (float) ; 

__attribute__((used)) static float noise_normalize(vorbis_look_psy *p, int limit, float *r, float *q, float *f, int *flags, float acc, int i, int n, int *out){

  vorbis_info_psy *vi=p->vi;
  float **sort = alloca(n*sizeof(*sort));
  int j,count=0;
  int start = (vi->normal_p ? vi->normal_start-i : n);
  if(start>n)start=n;

  /* force classic behavior where only energy in the current band is considered */
  acc=0.f;

  /* still responsible for populating *out where noise norm not in
     effect.  There's no need to [re]populate *q in these areas */
  for(j=0;j<start;j++){
    if(!flags || !flags[j]){ /* lossless coupling already quantized.
                                Don't touch; requantizing based on
                                energy would be incorrect. */
      float ve = q[j]/f[j];
      if(r[j]<0)
        out[j] = -rint(sqrt(ve));
      else
        out[j] = rint(sqrt(ve));
    }
  }

  /* sort magnitudes for noise norm portion of partition */
  for(;j<n;j++){
    if(!flags || !flags[j]){ /* can't noise norm elements that have
                                already been loslessly coupled; we can
                                only account for their energy error */
      float ve = q[j]/f[j];
      /* Despite all the new, more capable coupling code, for now we
         implement noise norm as it has been up to this point. Only
         consider promotions to unit magnitude from 0.  In addition
         the only energy error counted is quantizations to zero. */
      /* also-- the original point code only applied noise norm at > pointlimit */
      if(ve<.25f && (!flags || j>=limit-i)){
        acc += ve;
        sort[count++]=q+j; /* q is fabs(r) for unflagged element */
      }else{
        /* For now: no acc adjustment for nonzero quantization.  populate *out and q as this value is final. */
        if(r[j]<0)
          out[j] = -rint(sqrt(ve));
        else
          out[j] = rint(sqrt(ve));
        q[j] = out[j]*out[j]*f[j];
      }
    }/* else{
        again, no energy adjustment for error in nonzero quant-- for now
        }*/
  }

  if(count){
    /* noise norm to do */
    qsort(sort,count,sizeof(*sort),apsort);
    for(j=0;j<count;j++){
      int k=sort[j]-q;
      if(acc>=vi->normal_thresh){
        out[k]=unitnorm(r[k]);
        acc-=1.f;
        q[k]=f[k];
      }else{
        out[k]=0;
        q[k]=0.f;
      }
    }
  }

  return acc;
}