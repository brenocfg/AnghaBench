#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * packetblob; } ;
typedef  TYPE_1__ vorbis_block_internal ;
struct TYPE_10__ {int /*<<< orphan*/  sequence; int /*<<< orphan*/  granulepos; int /*<<< orphan*/  eofflag; int /*<<< orphan*/  opb; scalar_t__ res_bits; scalar_t__ floor_bits; scalar_t__ time_bits; scalar_t__ glue_bits; TYPE_1__* internal; } ;
typedef  TYPE_2__ vorbis_block ;
struct TYPE_11__ {int /*<<< orphan*/  packetno; int /*<<< orphan*/  granulepos; int /*<<< orphan*/  e_o_s; scalar_t__ b_o_s; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packet; } ;
typedef  TYPE_3__ ogg_packet ;
struct TYPE_12__ {int (* forward ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int OV_EINVAL ; 
 int PACKETBLOBS ; 
 TYPE_8__** _mapping_P ; 
 int /*<<< orphan*/  oggpack_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oggpack_get_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oggpack_reset (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*) ; 
 scalar_t__ vorbis_bitrate_managed (TYPE_2__*) ; 

int vorbis_analysis(vorbis_block *vb, ogg_packet *op){
  int ret,i;
  vorbis_block_internal *vbi=vb->internal;

  vb->glue_bits=0;
  vb->time_bits=0;
  vb->floor_bits=0;
  vb->res_bits=0;

  /* first things first.  Make sure encode is ready */
  for(i=0;i<PACKETBLOBS;i++)
    oggpack_reset(vbi->packetblob[i]);

  /* we only have one mapping type (0), and we let the mapping code
     itself figure out what soft mode to use.  This allows easier
     bitrate management */

  if((ret=_mapping_P[0]->forward(vb)))
    return(ret);

  if(op){
    if(vorbis_bitrate_managed(vb))
      /* The app is using a bitmanaged mode... but not using the
         bitrate management interface. */
      return(OV_EINVAL);

    op->packet=oggpack_get_buffer(&vb->opb);
    op->bytes=oggpack_bytes(&vb->opb);
    op->b_o_s=0;
    op->e_o_s=vb->eofflag;
    op->granulepos=vb->granulepos;
    op->packetno=vb->sequence; /* for sake of completeness */
  }
  return(0);
}