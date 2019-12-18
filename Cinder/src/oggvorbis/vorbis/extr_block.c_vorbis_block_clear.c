#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__** packetblob; } ;
typedef  TYPE_1__ vorbis_block_internal ;
struct TYPE_9__ {TYPE_1__* localstore; TYPE_1__* internal; } ;
typedef  TYPE_2__ vorbis_block ;

/* Variables and functions */
 int PACKETBLOBS ; 
 int /*<<< orphan*/  _ogg_free (TYPE_1__*) ; 
 int /*<<< orphan*/  _vorbis_block_ripcord (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oggpack_writeclear (TYPE_1__*) ; 

int vorbis_block_clear(vorbis_block *vb){
  int i;
  vorbis_block_internal *vbi=vb->internal;

  _vorbis_block_ripcord(vb);
  if(vb->localstore)_ogg_free(vb->localstore);

  if(vbi){
    for(i=0;i<PACKETBLOBS;i++){
      oggpack_writeclear(vbi->packetblob[i]);
      if(i!=PACKETBLOBS/2)_ogg_free(vbi->packetblob[i]);
    }
    _ogg_free(vbi);
  }
  memset(vb,0,sizeof(*vb));
  return(0);
}