#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int posts; int* forward_index; TYPE_4__* vi; } ;
typedef  TYPE_3__ vorbis_look_floor1 ;
typedef  int /*<<< orphan*/  vorbis_look_floor ;
struct TYPE_11__ {int mult; int* postlist; } ;
typedef  TYPE_4__ vorbis_info_floor1 ;
struct TYPE_12__ {size_t W; TYPE_2__* vd; } ;
typedef  TYPE_5__ vorbis_block ;
typedef  int ogg_int32_t ;
struct TYPE_13__ {int* blocksizes; } ;
typedef  TYPE_6__ codec_setup_info ;
struct TYPE_9__ {TYPE_1__* vi; } ;
struct TYPE_8__ {scalar_t__ codec_setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  render_line (int,int,int,int,int,int*) ; 

__attribute__((used)) static int floor1_inverse2(vorbis_block *vb,vorbis_look_floor *in,void *memo,
			  ogg_int32_t *out){
  vorbis_look_floor1 *look=(vorbis_look_floor1 *)in;
  vorbis_info_floor1 *info=look->vi;

  codec_setup_info   *ci=(codec_setup_info *)vb->vd->vi->codec_setup;
  int                  n=ci->blocksizes[vb->W]/2;
  int j;

  if(memo){
    /* render the lines */
    int *fit_value=(int *)memo;
    int hx=0;
    int lx=0;
    int ly=fit_value[0]*info->mult;
    for(j=1;j<look->posts;j++){
      int current=look->forward_index[j];
      int hy=fit_value[current]&0x7fff;
      if(hy==fit_value[current]){
	
	hy*=info->mult;
	hx=info->postlist[current];
	
	render_line(n,lx,hx,ly,hy,out);
	
	lx=hx;
	ly=hy;
      }
    }
    for(j=hx;j<n;j++)out[j]*=ly; /* be certain */    
    return(1);
  }
  memset(out,0,sizeof(*out)*n);
  return(0);
}