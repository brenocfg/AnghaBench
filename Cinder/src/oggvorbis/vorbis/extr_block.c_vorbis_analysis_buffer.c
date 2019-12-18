#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int channels; } ;
typedef  TYPE_1__ vorbis_info ;
struct TYPE_6__ {int pcm_current; int pcm_storage; float** pcm; float** pcmret; TYPE_3__* backend_state; TYPE_1__* vi; } ;
typedef  TYPE_2__ vorbis_dsp_state ;
struct TYPE_7__ {int /*<<< orphan*/ * header2; int /*<<< orphan*/ * header1; int /*<<< orphan*/ * header; } ;
typedef  TYPE_3__ private_state ;

/* Variables and functions */
 int /*<<< orphan*/  _ogg_free (int /*<<< orphan*/ *) ; 
 float* _ogg_realloc (float*,int) ; 

float **vorbis_analysis_buffer(vorbis_dsp_state *v, int vals){
  int i;
  vorbis_info *vi=v->vi;
  private_state *b=v->backend_state;

  /* free header, header1, header2 */
  if(b->header)_ogg_free(b->header);b->header=NULL;
  if(b->header1)_ogg_free(b->header1);b->header1=NULL;
  if(b->header2)_ogg_free(b->header2);b->header2=NULL;

  /* Do we have enough storage space for the requested buffer? If not,
     expand the PCM (and envelope) storage */

  if(v->pcm_current+vals>=v->pcm_storage){
    v->pcm_storage=v->pcm_current+vals*2;

    for(i=0;i<vi->channels;i++){
      v->pcm[i]=_ogg_realloc(v->pcm[i],v->pcm_storage*sizeof(*v->pcm[i]));
    }
  }

  for(i=0;i<vi->channels;i++)
    v->pcmret[i]=v->pcm[i]+v->pcm_current;

  return(v->pcmret);
}