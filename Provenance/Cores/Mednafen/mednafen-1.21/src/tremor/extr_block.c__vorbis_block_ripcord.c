#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct alloc_chain* reap; scalar_t__ localtop; scalar_t__ totaluse; scalar_t__ localalloc; int /*<<< orphan*/  localstore; } ;
typedef  TYPE_1__ vorbis_block ;
struct alloc_chain {struct alloc_chain* ptr; struct alloc_chain* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ogg_free (struct alloc_chain*) ; 
 int /*<<< orphan*/  _ogg_realloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct alloc_chain*,int /*<<< orphan*/ ,int) ; 

void _vorbis_block_ripcord(vorbis_block *vb){
  /* reap the chain */
  struct alloc_chain *reap=vb->reap;
  while(reap){
    struct alloc_chain *next=reap->next;
    _ogg_free(reap->ptr);
    memset(reap,0,sizeof(*reap));
    _ogg_free(reap);
    reap=next;
  }
  /* consolidate storage */
  if(vb->totaluse){
    vb->localstore=_ogg_realloc(vb->localstore,vb->totaluse+vb->localalloc);
    vb->localalloc+=vb->totaluse;
    vb->totaluse=0;
  }

  /* pull the ripcord */
  vb->localtop=0;
  vb->reap=NULL;
}