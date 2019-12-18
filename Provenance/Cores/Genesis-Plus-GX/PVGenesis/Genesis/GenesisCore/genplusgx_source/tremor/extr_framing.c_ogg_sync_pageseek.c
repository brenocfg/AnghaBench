#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  oggbyte_buffer ;
typedef  scalar_t__ ogg_uint32_t ;
struct TYPE_12__ {long fifo_fill; int headerbytes; long bodybytes; scalar_t__ fifo_head; TYPE_4__* fifo_tail; scalar_t__ unsynced; } ;
typedef  TYPE_2__ ogg_sync_state ;
struct TYPE_13__ {long header_len; long body_len; void* body; void* header; } ;
typedef  TYPE_3__ ogg_page ;
struct TYPE_14__ {int begin; long length; TYPE_1__* buffer; } ;
struct TYPE_11__ {unsigned char* data; } ;

/* Variables and functions */
 scalar_t__ _checksum (TYPE_4__*,long) ; 
 unsigned char* memchr (unsigned char*,char,long) ; 
 void* ogg_buffer_pretruncate (TYPE_4__*,long) ; 
 void* ogg_buffer_split (TYPE_4__**,scalar_t__*,long) ; 
 int /*<<< orphan*/  ogg_page_release (TYPE_3__*) ; 
 int /*<<< orphan*/  oggbyte_init (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int oggbyte_read1 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ oggbyte_read4 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  oggbyte_set4 (int /*<<< orphan*/ *,scalar_t__,int) ; 

long ogg_sync_pageseek(ogg_sync_state *oy,ogg_page *og){
  oggbyte_buffer page;
  long           bytes,ret=0;

  ogg_page_release(og);

  bytes=oy->fifo_fill;
  oggbyte_init(&page,oy->fifo_tail);

  if(oy->headerbytes==0){
    if(bytes<27)goto sync_out; /* not enough for even a minimal header */
    
    /* verify capture pattern */
    if(oggbyte_read1(&page,0)!=(int)'O' ||
       oggbyte_read1(&page,1)!=(int)'g' ||
       oggbyte_read1(&page,2)!=(int)'g' ||
       oggbyte_read1(&page,3)!=(int)'S'    ) goto sync_fail;

    oy->headerbytes=oggbyte_read1(&page,26)+27;
  }
  if(bytes<oy->headerbytes)goto sync_out; /* not enough for header +
                                             seg table */
  if(oy->bodybytes==0){
    int i;
    /* count up body length in the segment table */
    for(i=0;i<oy->headerbytes-27;i++)
      oy->bodybytes+=oggbyte_read1(&page,27+i);
  }
  
  if(oy->bodybytes+oy->headerbytes>bytes)goto sync_out;

  /* we have what appears to be a complete page; last test: verify
     checksum */
  {
    ogg_uint32_t chksum=oggbyte_read4(&page,22);
    oggbyte_set4(&page,0,22);

    /* Compare checksums; memory continues to be common access */
    if(chksum!=_checksum(oy->fifo_tail,oy->bodybytes+oy->headerbytes)){
      
      /* D'oh.  Mismatch! Corrupt page (or miscapture and not a page
         at all). replace the computed checksum with the one actually
         read in; remember all the memory is common access */
      
      oggbyte_set4(&page,chksum,22);
      goto sync_fail;
    }
    oggbyte_set4(&page,chksum,22);
  }

  /* We have a page.  Set up page return. */
  if(og){
    /* set up page output */
    og->header=ogg_buffer_split(&oy->fifo_tail,&oy->fifo_head,oy->headerbytes);
    og->header_len=oy->headerbytes;
    og->body=ogg_buffer_split(&oy->fifo_tail,&oy->fifo_head,oy->bodybytes);
    og->body_len=oy->bodybytes;
  }else{
    /* simply advance */
    oy->fifo_tail=
      ogg_buffer_pretruncate(oy->fifo_tail,oy->headerbytes+oy->bodybytes);
    if(!oy->fifo_tail)oy->fifo_head=0;
  }
  
  ret=oy->headerbytes+oy->bodybytes;
  oy->unsynced=0;
  oy->headerbytes=0;
  oy->bodybytes=0;
  oy->fifo_fill-=ret;

  return ret;
  
 sync_fail:

  oy->headerbytes=0;
  oy->bodybytes=0;
  oy->fifo_tail=ogg_buffer_pretruncate(oy->fifo_tail,1);
  ret--;
  
  /* search forward through fragments for possible capture */
  while(oy->fifo_tail){
    /* invariant: fifo_cursor points to a position in fifo_tail */
    unsigned char *now=oy->fifo_tail->buffer->data+oy->fifo_tail->begin;
    unsigned char *next=memchr(now, 'O', oy->fifo_tail->length);
      
    if(next){
      /* possible capture in this segment */
      long bytes=next-now;
      oy->fifo_tail=ogg_buffer_pretruncate(oy->fifo_tail,bytes);
      ret-=bytes;
      break;
    }else{
      /* no capture.  advance to next segment */
      long bytes=oy->fifo_tail->length;
      ret-=bytes;
      oy->fifo_tail=ogg_buffer_pretruncate(oy->fifo_tail,bytes);
    }
  }
  if(!oy->fifo_tail)oy->fifo_head=0;
  oy->fifo_fill+=ret;

 sync_out:
  return ret;
}