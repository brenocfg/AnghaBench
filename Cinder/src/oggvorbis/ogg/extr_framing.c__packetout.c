#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int lacing_returned; int lacing_packet; int* lacing_vals; scalar_t__ packetno; scalar_t__ body_returned; int /*<<< orphan*/ * granule_vals; scalar_t__ body_data; } ;
typedef  TYPE_1__ ogg_stream_state ;
struct TYPE_6__ {int e_o_s; int b_o_s; long bytes; int /*<<< orphan*/  granulepos; scalar_t__ packetno; scalar_t__ packet; } ;
typedef  TYPE_2__ ogg_packet ;

/* Variables and functions */

__attribute__((used)) static int _packetout(ogg_stream_state *os,ogg_packet *op,int adv){

  /* The last part of decode. We have the stream broken into packet
     segments.  Now we need to group them into packets (or return the
     out of sync markers) */

  int ptr=os->lacing_returned;

  if(os->lacing_packet<=ptr)return(0);

  if(os->lacing_vals[ptr]&0x400){
    /* we need to tell the codec there's a gap; it might need to
       handle previous packet dependencies. */
    os->lacing_returned++;
    os->packetno++;
    return(-1);
  }

  if(!op && !adv)return(1); /* just using peek as an inexpensive way
                               to ask if there's a whole packet
                               waiting */

  /* Gather the whole packet. We'll have no holes or a partial packet */
  {
    int size=os->lacing_vals[ptr]&0xff;
    long bytes=size;
    int eos=os->lacing_vals[ptr]&0x200; /* last packet of the stream? */
    int bos=os->lacing_vals[ptr]&0x100; /* first packet of the stream? */

    while(size==255){
      int val=os->lacing_vals[++ptr];
      size=val&0xff;
      if(val&0x200)eos=0x200;
      bytes+=size;
    }

    if(op){
      op->e_o_s=eos;
      op->b_o_s=bos;
      op->packet=os->body_data+os->body_returned;
      op->packetno=os->packetno;
      op->granulepos=os->granule_vals[ptr];
      op->bytes=bytes;
    }

    if(adv){
      os->body_returned+=bytes;
      os->lacing_returned=ptr+1;
      os->packetno++;
    }
  }
  return(1);
}