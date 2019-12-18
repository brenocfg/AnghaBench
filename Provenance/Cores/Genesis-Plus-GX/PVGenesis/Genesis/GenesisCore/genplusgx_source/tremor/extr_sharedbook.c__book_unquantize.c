#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int maptype; int dim; long entries; int /*<<< orphan*/  q_sequencep; int /*<<< orphan*/ * quantlist; int /*<<< orphan*/ * lengthlist; int /*<<< orphan*/  q_delta; int /*<<< orphan*/  q_min; } ;
typedef  TYPE_1__ static_codebook ;
typedef  int ogg_int32_t ;

/* Variables and functions */
 int VFLOAT_ADD (int,int,int,int,int*) ; 
 int VFLOAT_MULTI (int,int,int /*<<< orphan*/ ,int*) ; 
 int _book_maptype1_quantvals (TYPE_1__ const*) ; 
 int _float32_unpack (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ _ogg_calloc (int,int) ; 
 int /*<<< orphan*/  _ogg_free (int*) ; 
 int /*<<< orphan*/  abs (int /*<<< orphan*/ ) ; 

ogg_int32_t *_book_unquantize(const static_codebook *b,int n,int *sparsemap,
			      int *maxpoint){
  long j,k,count=0;
  if(b->maptype==1 || b->maptype==2){
    int quantvals;
    int minpoint,delpoint;
    ogg_int32_t mindel=_float32_unpack(b->q_min,&minpoint);
    ogg_int32_t delta=_float32_unpack(b->q_delta,&delpoint);
    ogg_int32_t *r=(ogg_int32_t *)_ogg_calloc(n*b->dim,sizeof(*r));
    int *rp=(int *)_ogg_calloc(n*b->dim,sizeof(*rp));

    *maxpoint=minpoint;

    /* maptype 1 and 2 both use a quantized value vector, but
       different sizes */
    switch(b->maptype){
    case 1:
      /* most of the time, entries%dimensions == 0, but we need to be
	 well defined.  We define that the possible vales at each
	 scalar is values == entries/dim.  If entries%dim != 0, we'll
	 have 'too few' values (values*dim<entries), which means that
	 we'll have 'left over' entries; left over entries use zeroed
	 values (and are wasted).  So don't generate codebooks like
	 that */
      quantvals=_book_maptype1_quantvals(b);
      for(j=0;j<b->entries;j++){
	if((sparsemap && b->lengthlist[j]) || !sparsemap){
	  ogg_int32_t last=0;
	  int lastpoint=0;
	  int indexdiv=1;
	  for(k=0;k<b->dim;k++){
	    int index= (j/indexdiv)%quantvals;
	    int point=0;
	    int val=VFLOAT_MULTI(delta,delpoint,
				 abs(b->quantlist[index]),&point);

	    val=VFLOAT_ADD(mindel,minpoint,val,point,&point);
	    val=VFLOAT_ADD(last,lastpoint,val,point,&point);
	    
	    if(b->q_sequencep){
	      last=val;	  
	      lastpoint=point;
	    }
	    
	    if(sparsemap){
	      r[sparsemap[count]*b->dim+k]=val;
	      rp[sparsemap[count]*b->dim+k]=point;
	    }else{
	      r[count*b->dim+k]=val;
	      rp[count*b->dim+k]=point;
	    }
	    if(*maxpoint<point)*maxpoint=point;
	    indexdiv*=quantvals;
	  }
	  count++;
	}

      }
      break;
    case 2:
      for(j=0;j<b->entries;j++){
	if((sparsemap && b->lengthlist[j]) || !sparsemap){
	  ogg_int32_t last=0;
	  int         lastpoint=0;

	  for(k=0;k<b->dim;k++){
	    int point=0;
	    int val=VFLOAT_MULTI(delta,delpoint,
				 abs(b->quantlist[j*b->dim+k]),&point);

	    val=VFLOAT_ADD(mindel,minpoint,val,point,&point);
	    val=VFLOAT_ADD(last,lastpoint,val,point,&point);
	    
	    if(b->q_sequencep){
	      last=val;	  
	      lastpoint=point;
	    }

	    if(sparsemap){
	      r[sparsemap[count]*b->dim+k]=val;
	      rp[sparsemap[count]*b->dim+k]=point;
	    }else{
	      r[count*b->dim+k]=val;
	      rp[count*b->dim+k]=point;
	    }
	    if(*maxpoint<point)*maxpoint=point;
	  }
	  count++;
	}
      }
      break;
    }

    for(j=0;j<n*b->dim;j++)
      if(rp[j]<*maxpoint)
	r[j]>>=*maxpoint-rp[j];
	    
    _ogg_free(rp);
    return(r);
  }
  return(NULL);
}