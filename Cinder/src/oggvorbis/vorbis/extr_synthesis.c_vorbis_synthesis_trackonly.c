#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_7__* codec_setup; } ;
typedef  TYPE_2__ vorbis_info ;
struct TYPE_13__ {TYPE_2__* vi; TYPE_5__* backend_state; } ;
typedef  TYPE_3__ vorbis_dsp_state ;
struct TYPE_14__ {int mode; int nW; int /*<<< orphan*/ * pcm; scalar_t__ pcmend; int /*<<< orphan*/  eofflag; int /*<<< orphan*/  sequence; int /*<<< orphan*/  granulepos; void* lW; scalar_t__ W; int /*<<< orphan*/  opb; TYPE_3__* vd; } ;
typedef  TYPE_4__ vorbis_block ;
struct TYPE_15__ {int modebits; } ;
typedef  TYPE_5__ private_state ;
typedef  int /*<<< orphan*/  oggpack_buffer ;
struct TYPE_16__ {int /*<<< orphan*/  e_o_s; int /*<<< orphan*/  packetno; int /*<<< orphan*/  granulepos; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packet; } ;
typedef  TYPE_6__ ogg_packet ;
struct TYPE_17__ {TYPE_1__** mode_param; } ;
typedef  TYPE_7__ codec_setup_info ;
struct TYPE_11__ {scalar_t__ blockflag; } ;

/* Variables and functions */
 int OV_EBADPACKET ; 
 int OV_ENOTAUDIO ; 
 int /*<<< orphan*/  _vorbis_block_ripcord (TYPE_4__*) ; 
 void* oggpack_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  oggpack_readinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vorbis_synthesis_trackonly(vorbis_block *vb,ogg_packet *op){
  vorbis_dsp_state     *vd=vb->vd;
  private_state        *b=vd->backend_state;
  vorbis_info          *vi=vd->vi;
  codec_setup_info     *ci=vi->codec_setup;
  oggpack_buffer       *opb=&vb->opb;
  int                   mode;

  /* first things first.  Make sure decode is ready */
  _vorbis_block_ripcord(vb);
  oggpack_readinit(opb,op->packet,op->bytes);

  /* Check the packet type */
  if(oggpack_read(opb,1)!=0){
    /* Oops.  This is not an audio data packet */
    return(OV_ENOTAUDIO);
  }

  /* read our mode and pre/post windowsize */
  mode=oggpack_read(opb,b->modebits);
  if(mode==-1)return(OV_EBADPACKET);

  vb->mode=mode;
  if(!ci->mode_param[mode]){
    return(OV_EBADPACKET);
  }
  
  vb->W=ci->mode_param[mode]->blockflag;
  if(vb->W){
    vb->lW=oggpack_read(opb,1);
    vb->nW=oggpack_read(opb,1);
    if(vb->nW==-1)   return(OV_EBADPACKET);
  }else{
    vb->lW=0;
    vb->nW=0;
  }

  /* more setup */
  vb->granulepos=op->granulepos;
  vb->sequence=op->packetno;
  vb->eofflag=op->e_o_s;

  /* no pcm */
  vb->pcmend=0;
  vb->pcm=NULL;

  return(0);
}