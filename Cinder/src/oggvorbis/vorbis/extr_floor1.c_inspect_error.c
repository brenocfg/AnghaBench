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
struct TYPE_3__ {float const twofitatten; int maxover; int maxunder; int maxerr; } ;
typedef  TYPE_1__ vorbis_info_floor1 ;

/* Variables and functions */
 int abs (int) ; 
 int vorbis_dBquant (float const*) ; 

__attribute__((used)) static int inspect_error(int x0,int x1,int y0,int y1,const float *mask,
                         const float *mdct,
                         vorbis_info_floor1 *info){
  int dy=y1-y0;
  int adx=x1-x0;
  int ady=abs(dy);
  int base=dy/adx;
  int sy=(dy<0?base-1:base+1);
  int x=x0;
  int y=y0;
  int err=0;
  int val=vorbis_dBquant(mask+x);
  int mse=0;
  int n=0;

  ady-=abs(base*adx);

  mse=(y-val);
  mse*=mse;
  n++;
  if(mdct[x]+info->twofitatten>=mask[x]){
    if(y+info->maxover<val)return(1);
    if(y-info->maxunder>val)return(1);
  }

  while(++x<x1){
    err=err+ady;
    if(err>=adx){
      err-=adx;
      y+=sy;
    }else{
      y+=base;
    }

    val=vorbis_dBquant(mask+x);
    mse+=((y-val)*(y-val));
    n++;
    if(mdct[x]+info->twofitatten>=mask[x]){
      if(val){
        if(y+info->maxover<val)return(1);
        if(y-info->maxunder>val)return(1);
      }
    }
  }

  if(info->maxover*info->maxover/n>info->maxerr)return(0);
  if(info->maxunder*info->maxunder/n>info->maxerr)return(0);
  if(mse/n>info->maxerr)return(1);
  return(0);
}