#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {int* chmuxlist; size_t* floorsubmap; int coupling_steps; size_t* coupling_mag; size_t* coupling_ang; int submaps; size_t* residuesubmap; } ;
typedef  TYPE_1__ vorbis_info_mapping0 ;
typedef  int /*<<< orphan*/  vorbis_info_mapping ;
struct TYPE_16__ {int channels; TYPE_6__* codec_setup; } ;
typedef  TYPE_2__ vorbis_info ;
struct TYPE_17__ {TYPE_5__* backend_state; TYPE_2__* vi; } ;
typedef  TYPE_3__ vorbis_dsp_state ;
struct TYPE_18__ {long pcmend; size_t W; float** pcm; TYPE_3__* vd; } ;
typedef  TYPE_4__ vorbis_block ;
struct TYPE_19__ {int /*<<< orphan*/ ** transform; int /*<<< orphan*/ * flr; int /*<<< orphan*/ * residue; } ;
typedef  TYPE_5__ private_state ;
struct TYPE_20__ {long* blocksizes; size_t* floor_type; size_t* residue_type; } ;
typedef  TYPE_6__ codec_setup_info ;
struct TYPE_14__ {int /*<<< orphan*/  (* inverse2 ) (TYPE_4__*,int /*<<< orphan*/ ,void*,float*) ;void* (* inverse1 ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* inverse ) (TYPE_4__*,int /*<<< orphan*/ ,float**,int*,int) ;} ;

/* Variables and functions */
 TYPE_12__** _floor_P ; 
 TYPE_11__** _residue_P ; 
 void* alloca (int) ; 
 int /*<<< orphan*/  mdct_backward (int /*<<< orphan*/ ,float*,float*) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 void* stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ,float**,int*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,int /*<<< orphan*/ ,void*,float*) ; 

__attribute__((used)) static int mapping0_inverse(vorbis_block *vb,vorbis_info_mapping *l){
  vorbis_dsp_state     *vd=vb->vd;
  vorbis_info          *vi=vd->vi;
  codec_setup_info     *ci=vi->codec_setup;
  private_state        *b=vd->backend_state;
  vorbis_info_mapping0 *info=(vorbis_info_mapping0 *)l;

  int                   i,j;
  long                  n=vb->pcmend=ci->blocksizes[vb->W];

  float **pcmbundle=alloca(sizeof(*pcmbundle)*vi->channels);
  int    *zerobundle=alloca(sizeof(*zerobundle)*vi->channels);

  int   *nonzero  =alloca(sizeof(*nonzero)*vi->channels);
  void **floormemo=alloca(sizeof(*floormemo)*vi->channels);

  /* recover the spectral envelope; store it in the PCM vector for now */
  for(i=0;i<vi->channels;i++){
    int submap=info->chmuxlist[i];
    floormemo[i]=_floor_P[ci->floor_type[info->floorsubmap[submap]]]->
      inverse1(vb,b->flr[info->floorsubmap[submap]]);
    if(floormemo[i])
      nonzero[i]=1;
    else
      nonzero[i]=0;
    memset(vb->pcm[i],0,sizeof(*vb->pcm[i])*n/2);
  }

  /* channel coupling can 'dirty' the nonzero listing */
  for(i=0;i<info->coupling_steps;i++){
    if(nonzero[info->coupling_mag[i]] ||
       nonzero[info->coupling_ang[i]]){
      nonzero[info->coupling_mag[i]]=1;
      nonzero[info->coupling_ang[i]]=1;
    }
  }

  /* recover the residue into our working vectors */
  for(i=0;i<info->submaps;i++){
    int ch_in_bundle=0;
    for(j=0;j<vi->channels;j++){
      if(info->chmuxlist[j]==i){
        if(nonzero[j])
          zerobundle[ch_in_bundle]=1;
        else
          zerobundle[ch_in_bundle]=0;
        pcmbundle[ch_in_bundle++]=vb->pcm[j];
      }
    }

    _residue_P[ci->residue_type[info->residuesubmap[i]]]->
      inverse(vb,b->residue[info->residuesubmap[i]],
              pcmbundle,zerobundle,ch_in_bundle);
  }

  /* channel coupling */
  for(i=info->coupling_steps-1;i>=0;i--){
    float *pcmM=vb->pcm[info->coupling_mag[i]];
    float *pcmA=vb->pcm[info->coupling_ang[i]];

    for(j=0;j<n/2;j++){
      float mag=pcmM[j];
      float ang=pcmA[j];

      if(mag>0)
        if(ang>0){
          pcmM[j]=mag;
          pcmA[j]=mag-ang;
        }else{
          pcmA[j]=mag;
          pcmM[j]=mag+ang;
        }
      else
        if(ang>0){
          pcmM[j]=mag;
          pcmA[j]=mag+ang;
        }else{
          pcmA[j]=mag;
          pcmM[j]=mag-ang;
        }
    }
  }

  /* compute and apply spectral envelope */
  for(i=0;i<vi->channels;i++){
    float *pcm=vb->pcm[i];
    int submap=info->chmuxlist[i];
    _floor_P[ci->floor_type[info->floorsubmap[submap]]]->
      inverse2(vb,b->flr[info->floorsubmap[submap]],
               floormemo[i],pcm);
  }

  /* transform the PCM data; takes PCM vector, vb; modifies PCM vector */
  /* only MDCT right now.... */
  for(i=0;i<vi->channels;i++){
    float *pcm=vb->pcm[i];
    mdct_backward(b->transform[vb->W][0],pcm,pcm);
  }

  /* all done! */
  return(0);
}