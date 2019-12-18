#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* unused_buffers; int /*<<< orphan*/  outstanding; } ;
typedef  TYPE_2__ ogg_buffer_state ;
struct TYPE_6__ {TYPE_2__* owner; TYPE_3__* next; } ;
struct TYPE_8__ {long size; int refcount; TYPE_1__ ptr; void* data; } ;
typedef  TYPE_3__ ogg_buffer ;

/* Variables and functions */
 void* _ogg_malloc (int) ; 
 void* _ogg_realloc (void*,long) ; 

__attribute__((used)) static ogg_buffer *_fetch_buffer(ogg_buffer_state *bs,long bytes){
  ogg_buffer    *ob;
  bs->outstanding++;

  /* do we have an unused buffer sitting in the pool? */
  if(bs->unused_buffers){
    ob=bs->unused_buffers;
    bs->unused_buffers=ob->ptr.next;

    /* if the unused buffer is too small, grow it */
    if(ob->size<bytes){
      ob->data=_ogg_realloc(ob->data,bytes);
      ob->size=bytes;
    }
  }else{
    /* allocate a new buffer */
    ob=_ogg_malloc(sizeof(*ob));
    ob->data=_ogg_malloc(bytes<16?16:bytes);
    ob->size=bytes;
  }

  ob->refcount=1;
  ob->ptr.owner=bs;
  return ob;
}