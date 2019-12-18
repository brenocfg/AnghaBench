#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ localstore; } ;
typedef  TYPE_1__ vorbis_block ;

/* Variables and functions */
 int /*<<< orphan*/  _ogg_free (scalar_t__) ; 
 int /*<<< orphan*/  _vorbis_block_ripcord (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int vorbis_block_clear(vorbis_block *vb){
  _vorbis_block_ripcord(vb);
  if(vb->localstore)_ogg_free(vb->localstore);

  memset(vb,0,sizeof(*vb));
  return(0);
}