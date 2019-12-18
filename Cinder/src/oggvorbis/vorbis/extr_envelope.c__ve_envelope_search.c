#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vorbis_info_psy_global ;
struct TYPE_9__ {TYPE_5__* codec_setup; } ;
typedef  TYPE_1__ vorbis_info ;
struct TYPE_10__ {int pcm_current; float** pcm; long centerW; size_t W; scalar_t__ backend_state; TYPE_1__* vi; } ;
typedef  TYPE_2__ vorbis_dsp_state ;
struct TYPE_11__ {TYPE_4__* ve; } ;
typedef  TYPE_3__ private_state ;
struct TYPE_12__ {int current; int searchstep; int storage; int* mark; int stretch; long ch; long cursor; long curmark; TYPE_8__* filter; int /*<<< orphan*/  band; } ;
typedef  TYPE_4__ envelope_lookup ;
struct TYPE_13__ {int* blocksizes; int /*<<< orphan*/  psy_g_param; } ;
typedef  TYPE_5__ codec_setup_info ;
struct TYPE_14__ {double* markers; } ;

/* Variables and functions */
 long VE_BANDS ; 
 int VE_MAXSTRETCH ; 
 int VE_POST ; 
 int VE_WIN ; 
 int /*<<< orphan*/  _analysis_output_always (char*,int,float*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* _ogg_realloc (int*,int) ; 
 int _ve_amp (TYPE_4__*,int /*<<< orphan*/ *,float*,int /*<<< orphan*/ ,TYPE_8__*) ; 
 float* alloca (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int seq ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int totalshift ; 

long _ve_envelope_search(vorbis_dsp_state *v){
  vorbis_info *vi=v->vi;
  codec_setup_info *ci=vi->codec_setup;
  vorbis_info_psy_global *gi=&ci->psy_g_param;
  envelope_lookup *ve=((private_state *)(v->backend_state))->ve;
  long i,j;

  int first=ve->current/ve->searchstep;
  int last=v->pcm_current/ve->searchstep-VE_WIN;
  if(first<0)first=0;

  /* make sure we have enough storage to match the PCM */
  if(last+VE_WIN+VE_POST>ve->storage){
    ve->storage=last+VE_WIN+VE_POST; /* be sure */
    ve->mark=_ogg_realloc(ve->mark,ve->storage*sizeof(*ve->mark));
  }

  for(j=first;j<last;j++){
    int ret=0;

    ve->stretch++;
    if(ve->stretch>VE_MAXSTRETCH*2)
      ve->stretch=VE_MAXSTRETCH*2;

    for(i=0;i<ve->ch;i++){
      float *pcm=v->pcm[i]+ve->searchstep*(j);
      ret|=_ve_amp(ve,gi,pcm,ve->band,ve->filter+i*VE_BANDS);
    }

    ve->mark[j+VE_POST]=0;
    if(ret&1){
      ve->mark[j]=1;
      ve->mark[j+1]=1;
    }

    if(ret&2){
      ve->mark[j]=1;
      if(j>0)ve->mark[j-1]=1;
    }

    if(ret&4)ve->stretch=-1;
  }

  ve->current=last*ve->searchstep;

  {
    long centerW=v->centerW;
    long testW=
      centerW+
      ci->blocksizes[v->W]/4+
      ci->blocksizes[1]/2+
      ci->blocksizes[0]/4;

    j=ve->cursor;

    while(j<ve->current-(ve->searchstep)){/* account for postecho
                                             working back one window */
      if(j>=testW)return(1);

      ve->cursor=j;

      if(ve->mark[j/ve->searchstep]){
        if(j>centerW){

#if 0
          if(j>ve->curmark){
            float *marker=alloca(v->pcm_current*sizeof(*marker));
            int l,m;
            memset(marker,0,sizeof(*marker)*v->pcm_current);
            fprintf(stderr,"mark! seq=%d, cursor:%fs time:%fs\n",
                    seq,
                    (totalshift+ve->cursor)/44100.,
                    (totalshift+j)/44100.);
            _analysis_output_always("pcmL",seq,v->pcm[0],v->pcm_current,0,0,totalshift);
            _analysis_output_always("pcmR",seq,v->pcm[1],v->pcm_current,0,0,totalshift);

            _analysis_output_always("markL",seq,v->pcm[0],j,0,0,totalshift);
            _analysis_output_always("markR",seq,v->pcm[1],j,0,0,totalshift);

            for(m=0;m<VE_BANDS;m++){
              char buf[80];
              sprintf(buf,"delL%d",m);
              for(l=0;l<last;l++)marker[l*ve->searchstep]=ve->filter[m].markers[l]*.1;
              _analysis_output_always(buf,seq,marker,v->pcm_current,0,0,totalshift);
            }

            for(m=0;m<VE_BANDS;m++){
              char buf[80];
              sprintf(buf,"delR%d",m);
              for(l=0;l<last;l++)marker[l*ve->searchstep]=ve->filter[m+VE_BANDS].markers[l]*.1;
              _analysis_output_always(buf,seq,marker,v->pcm_current,0,0,totalshift);
            }

            for(l=0;l<last;l++)marker[l*ve->searchstep]=ve->mark[l]*.4;
            _analysis_output_always("mark",seq,marker,v->pcm_current,0,0,totalshift);


            seq++;

          }
#endif

          ve->curmark=j;
          if(j>=testW)return(1);
          return(0);
        }
      }
      j+=ve->searchstep;
    }
  }

  return(-1);
}