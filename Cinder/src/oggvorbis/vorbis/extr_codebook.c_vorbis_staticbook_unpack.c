#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int allocedp; int dim; int entries; long* lengthlist; int maptype; int q_min; int q_delta; int q_quant; int q_sequencep; int* quantlist; } ;
typedef  TYPE_1__ static_codebook ;
struct TYPE_11__ {int storage; } ;
typedef  TYPE_2__ oggpack_buffer ;

/* Variables and functions */
 int _book_maptype1_quantvals (TYPE_1__*) ; 
 int _ilog (long) ; 
 TYPE_1__* _ogg_calloc (int,int) ; 
 void* _ogg_malloc (int) ; 
 int oggpack_bytes (TYPE_2__*) ; 
 int oggpack_read (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vorbis_staticbook_destroy (TYPE_1__*) ; 

static_codebook *vorbis_staticbook_unpack(oggpack_buffer *opb){
  long i,j;
  static_codebook *s=_ogg_calloc(1,sizeof(*s));
  s->allocedp=1;

  /* make sure alignment is correct */
  if(oggpack_read(opb,24)!=0x564342)goto _eofout;

  /* first the basic parameters */
  s->dim=oggpack_read(opb,16);
  s->entries=oggpack_read(opb,24);
  if(s->entries==-1)goto _eofout;

  if(_ilog(s->dim)+_ilog(s->entries)>24)goto _eofout;

  /* codeword ordering.... length ordered or unordered? */
  switch((int)oggpack_read(opb,1)){
  case 0:{
    long unused;
    /* allocated but unused entries? */
    unused=oggpack_read(opb,1);
    if((s->entries*(unused?1:5)+7)>>3>opb->storage-oggpack_bytes(opb))
      goto _eofout;
    /* unordered */
    s->lengthlist=_ogg_malloc(sizeof(*s->lengthlist)*s->entries);

    /* allocated but unused entries? */
    if(unused){
      /* yes, unused entries */

      for(i=0;i<s->entries;i++){
        if(oggpack_read(opb,1)){
          long num=oggpack_read(opb,5);
          if(num==-1)goto _eofout;
          s->lengthlist[i]=num+1;
        }else
          s->lengthlist[i]=0;
      }
    }else{
      /* all entries used; no tagging */
      for(i=0;i<s->entries;i++){
        long num=oggpack_read(opb,5);
        if(num==-1)goto _eofout;
        s->lengthlist[i]=num+1;
      }
    }

    break;
  }
  case 1:
    /* ordered */
    {
      long length=oggpack_read(opb,5)+1;
      if(length==0)goto _eofout;
      s->lengthlist=_ogg_malloc(sizeof(*s->lengthlist)*s->entries);

      for(i=0;i<s->entries;){
        long num=oggpack_read(opb,_ilog(s->entries-i));
        if(num==-1)goto _eofout;
        if(length>32 || num>s->entries-i ||
           (num>0 && (num-1)>>(length-1)>1)){
          goto _errout;
        }
        if(length>32)goto _errout;
        for(j=0;j<num;j++,i++)
          s->lengthlist[i]=length;
        length++;
      }
    }
    break;
  default:
    /* EOF */
    goto _eofout;
  }

  /* Do we have a mapping to unpack? */
  switch((s->maptype=oggpack_read(opb,4))){
  case 0:
    /* no mapping */
    break;
  case 1: case 2:
    /* implicitly populated value mapping */
    /* explicitly populated value mapping */

    s->q_min=oggpack_read(opb,32);
    s->q_delta=oggpack_read(opb,32);
    s->q_quant=oggpack_read(opb,4)+1;
    s->q_sequencep=oggpack_read(opb,1);
    if(s->q_sequencep==-1)goto _eofout;

    {
      int quantvals=0;
      switch(s->maptype){
      case 1:
        quantvals=(s->dim==0?0:_book_maptype1_quantvals(s));
        break;
      case 2:
        quantvals=s->entries*s->dim;
        break;
      }

      /* quantized values */
      if(((quantvals*s->q_quant+7)>>3)>opb->storage-oggpack_bytes(opb))
        goto _eofout;
      s->quantlist=_ogg_malloc(sizeof(*s->quantlist)*quantvals);
      for(i=0;i<quantvals;i++)
        s->quantlist[i]=oggpack_read(opb,s->q_quant);

      if(quantvals&&s->quantlist[quantvals-1]==-1)goto _eofout;
    }
    break;
  default:
    goto _errout;
  }

  /* all set */
  return(s);

 _errout:
 _eofout:
  vorbis_staticbook_destroy(s);
  return(NULL);
}