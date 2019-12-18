#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float eighth_octave_lines; int shiftoc; int firstoc; long total_octave_lines; float* ath; int* octave; long* bark; int n; long rate; int m_val; int** noiseoffset; TYPE_3__* vi; int /*<<< orphan*/  tonecurves; } ;
typedef  TYPE_1__ vorbis_look_psy ;
struct TYPE_9__ {float eighth_octave_lines; } ;
typedef  TYPE_2__ vorbis_info_psy_global ;
struct TYPE_10__ {long noisewindowlomin; float noisewindowlo; long noisewindowhimin; float noisewindowhi; int** noiseoff; int /*<<< orphan*/  tone_decay; int /*<<< orphan*/  tone_centerboost; int /*<<< orphan*/  toneatt; } ;
typedef  TYPE_3__ vorbis_info_psy ;

/* Variables and functions */
 float* ATH ; 
 int MAX_ATH ; 
 int P_BANDS ; 
 int P_NOISECURVES ; 
 int /*<<< orphan*/  _analysis_output_always (char*,int,int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* _ogg_malloc (int) ; 
 int fromOC (long) ; 
 int log (float) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int rint (int) ; 
 int /*<<< orphan*/  setup_tone_curves (int /*<<< orphan*/ ,long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float toBARK (long) ; 
 int toOC (long) ; 

void _vp_psy_init(vorbis_look_psy *p,vorbis_info_psy *vi,
                  vorbis_info_psy_global *gi,int n,long rate){
  long i,j,lo=-99,hi=1;
  long maxoc;
  memset(p,0,sizeof(*p));

  p->eighth_octave_lines=gi->eighth_octave_lines;
  p->shiftoc=rint(log(gi->eighth_octave_lines*8.f)/log(2.f))-1;

  p->firstoc=toOC(.25f*rate*.5/n)*(1<<(p->shiftoc+1))-gi->eighth_octave_lines;
  maxoc=toOC((n+.25f)*rate*.5/n)*(1<<(p->shiftoc+1))+.5f;
  p->total_octave_lines=maxoc-p->firstoc+1;
  p->ath=_ogg_malloc(n*sizeof(*p->ath));

  p->octave=_ogg_malloc(n*sizeof(*p->octave));
  p->bark=_ogg_malloc(n*sizeof(*p->bark));
  p->vi=vi;
  p->n=n;
  p->rate=rate;

  /* AoTuV HF weighting */
  p->m_val = 1.;
  if(rate < 26000) p->m_val = 0;
  else if(rate < 38000) p->m_val = .94;   /* 32kHz */
  else if(rate > 46000) p->m_val = 1.275; /* 48kHz */

  /* set up the lookups for a given blocksize and sample rate */

  for(i=0,j=0;i<MAX_ATH-1;i++){
    int endpos=rint(fromOC((i+1)*.125-2.)*2*n/rate);
    float base=ATH[i];
    if(j<endpos){
      float delta=(ATH[i+1]-base)/(endpos-j);
      for(;j<endpos && j<n;j++){
        p->ath[j]=base+100.;
        base+=delta;
      }
    }
  }

  for(;j<n;j++){
    p->ath[j]=p->ath[j-1];
  }

  for(i=0;i<n;i++){
    float bark=toBARK(rate/(2*n)*i);

    for(;lo+vi->noisewindowlomin<i &&
          toBARK(rate/(2*n)*lo)<(bark-vi->noisewindowlo);lo++);

    for(;hi<=n && (hi<i+vi->noisewindowhimin ||
          toBARK(rate/(2*n)*hi)<(bark+vi->noisewindowhi));hi++);

    p->bark[i]=((lo-1)<<16)+(hi-1);

  }

  for(i=0;i<n;i++)
    p->octave[i]=toOC((i+.25f)*.5*rate/n)*(1<<(p->shiftoc+1))+.5f;

  p->tonecurves=setup_tone_curves(vi->toneatt,rate*.5/n,n,
                                  vi->tone_centerboost,vi->tone_decay);

  /* set up rolling noise median */
  p->noiseoffset=_ogg_malloc(P_NOISECURVES*sizeof(*p->noiseoffset));
  for(i=0;i<P_NOISECURVES;i++)
    p->noiseoffset[i]=_ogg_malloc(n*sizeof(**p->noiseoffset));

  for(i=0;i<n;i++){
    float halfoc=toOC((i+.5)*rate/(2.*n))*2.;
    int inthalfoc;
    float del;

    if(halfoc<0)halfoc=0;
    if(halfoc>=P_BANDS-1)halfoc=P_BANDS-1;
    inthalfoc=(int)halfoc;
    del=halfoc-inthalfoc;

    for(j=0;j<P_NOISECURVES;j++)
      p->noiseoffset[j][i]=
        p->vi->noiseoff[j][inthalfoc]*(1.-del) +
        p->vi->noiseoff[j][inthalfoc+1]*del;

  }
#if 0
  {
    static int ls=0;
    _analysis_output_always("noiseoff0",ls,p->noiseoffset[0],n,1,0,0);
    _analysis_output_always("noiseoff1",ls,p->noiseoffset[1],n,1,0,0);
    _analysis_output_always("noiseoff2",ls++,p->noiseoffset[2],n,1,0,0);
  }
#endif
}