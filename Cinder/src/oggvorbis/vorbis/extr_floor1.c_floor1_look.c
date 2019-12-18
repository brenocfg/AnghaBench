#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int n; int posts; int* forward_index; int* reverse_index; int* sorted_index; int quant_q; int* loneighbor; int* hineighbor; TYPE_3__* vi; } ;
typedef  TYPE_1__ vorbis_look_floor1 ;
typedef  TYPE_1__ vorbis_look_floor ;
struct TYPE_7__ {int* postlist; int partitions; size_t* partitionclass; int mult; scalar_t__* class_dim; } ;
typedef  TYPE_3__ vorbis_info_floor1 ;
typedef  int /*<<< orphan*/  vorbis_info_floor ;
typedef  int /*<<< orphan*/  vorbis_dsp_state ;

/* Variables and functions */
 int /*<<< orphan*/  VIF_POSIT ; 
 TYPE_1__* _ogg_calloc (int,int) ; 
 int /*<<< orphan*/  icomp ; 
 int /*<<< orphan*/  qsort (int**,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vorbis_look_floor *floor1_look(vorbis_dsp_state *vd,
                                      vorbis_info_floor *in){

  int *sortpointer[VIF_POSIT+2];
  vorbis_info_floor1 *info=(vorbis_info_floor1 *)in;
  vorbis_look_floor1 *look=_ogg_calloc(1,sizeof(*look));
  int i,j,n=0;

  (void)vd;

  look->vi=info;
  look->n=info->postlist[1];

  /* we drop each position value in-between already decoded values,
     and use linear interpolation to predict each new value past the
     edges.  The positions are read in the order of the position
     list... we precompute the bounding positions in the lookup.  Of
     course, the neighbors can change (if a position is declined), but
     this is an initial mapping */

  for(i=0;i<info->partitions;i++)n+=info->class_dim[info->partitionclass[i]];
  n+=2;
  look->posts=n;

  /* also store a sorted position index */
  for(i=0;i<n;i++)sortpointer[i]=info->postlist+i;
  qsort(sortpointer,n,sizeof(*sortpointer),icomp);

  /* points from sort order back to range number */
  for(i=0;i<n;i++)look->forward_index[i]=sortpointer[i]-info->postlist;
  /* points from range order to sorted position */
  for(i=0;i<n;i++)look->reverse_index[look->forward_index[i]]=i;
  /* we actually need the post values too */
  for(i=0;i<n;i++)look->sorted_index[i]=info->postlist[look->forward_index[i]];

  /* quantize values to multiplier spec */
  switch(info->mult){
  case 1: /* 1024 -> 256 */
    look->quant_q=256;
    break;
  case 2: /* 1024 -> 128 */
    look->quant_q=128;
    break;
  case 3: /* 1024 -> 86 */
    look->quant_q=86;
    break;
  case 4: /* 1024 -> 64 */
    look->quant_q=64;
    break;
  }

  /* discover our neighbors for decode where we don't use fit flags
     (that would push the neighbors outward) */
  for(i=0;i<n-2;i++){
    int lo=0;
    int hi=1;
    int lx=0;
    int hx=look->n;
    int currentx=info->postlist[i+2];
    for(j=0;j<i+2;j++){
      int x=info->postlist[j];
      if(x>lx && x<currentx){
        lo=j;
        lx=x;
      }
      if(x<hx && x>currentx){
        hi=j;
        hx=x;
      }
    }
    look->loneighbor[i]=lo;
    look->hineighbor[i]=hi;
  }

  return(look);
}