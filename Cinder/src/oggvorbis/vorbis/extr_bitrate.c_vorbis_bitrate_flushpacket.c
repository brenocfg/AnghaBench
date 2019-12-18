#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* backend_state; } ;
typedef  TYPE_1__ vorbis_dsp_state ;
struct TYPE_11__ {int /*<<< orphan*/ * packetblob; } ;
typedef  TYPE_2__ vorbis_block_internal ;
struct TYPE_12__ {int /*<<< orphan*/  sequence; int /*<<< orphan*/  granulepos; int /*<<< orphan*/  eofflag; TYPE_2__* internal; } ;
typedef  TYPE_3__ vorbis_block ;
struct TYPE_15__ {int choice; TYPE_3__* vb; } ;
struct TYPE_13__ {TYPE_6__ bms; } ;
typedef  TYPE_4__ private_state ;
struct TYPE_14__ {int /*<<< orphan*/  packetno; int /*<<< orphan*/  granulepos; int /*<<< orphan*/  e_o_s; scalar_t__ b_o_s; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packet; } ;
typedef  TYPE_5__ ogg_packet ;
typedef  TYPE_6__ bitrate_manager_state ;

/* Variables and functions */
 int PACKETBLOBS ; 
 int /*<<< orphan*/  oggpack_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oggpack_get_buffer (int /*<<< orphan*/ ) ; 
 scalar_t__ vorbis_bitrate_managed (TYPE_3__*) ; 

int vorbis_bitrate_flushpacket(vorbis_dsp_state *vd,ogg_packet *op){
  private_state         *b=vd->backend_state;
  bitrate_manager_state *bm=&b->bms;
  vorbis_block          *vb=bm->vb;
  int                    choice=PACKETBLOBS/2;
  if(!vb)return 0;

  if(op){
    vorbis_block_internal *vbi=vb->internal;

    if(vorbis_bitrate_managed(vb))
      choice=bm->choice;

    op->packet=oggpack_get_buffer(vbi->packetblob[choice]);
    op->bytes=oggpack_bytes(vbi->packetblob[choice]);
    op->b_o_s=0;
    op->e_o_s=vb->eofflag;
    op->granulepos=vb->granulepos;
    op->packetno=vb->sequence; /* for sake of completeness */
  }

  bm->vb=0;
  return(1);
}