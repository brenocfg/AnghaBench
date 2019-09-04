#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * qr_point ;
struct TYPE_8__ {int** fwd; int fwd22; } ;
typedef  TYPE_1__ qr_hom ;
struct TYPE_9__ {int* o; int* size; } ;
typedef  TYPE_2__ qr_finder ;

/* Variables and functions */
 int bch15_5_correct (unsigned int*) ; 
 int /*<<< orphan*/  qr_hom_fproject (int /*<<< orphan*/ *,TYPE_1__ const*,int,int,int) ; 
 int qr_img_get_bit (unsigned char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qr_finder_fmt_info_decode(qr_finder *_ul,qr_finder *_ur,
 qr_finder *_dl,const qr_hom *_hom,
 const unsigned char *_img,int _width,int _height){
  qr_point p;
  unsigned lo[2];
  unsigned hi[2];
  int      u;
  int      v;
  int      x;
  int      y;
  int      w;
  int      dx;
  int      dy;
  int      dw;
  int      fmt_info[4];
  int      count[4];
  int      nerrs[4];
  int      nfmt_info;
  int      besti;
  int      imax;
  int      di;
  int      i;
  int      k;
  /*Read the bits around the UL corner.*/
  lo[0]=0;
  u=_ul->o[0]+5*_ul->size[0];
  v=_ul->o[1]-3*_ul->size[1];
  x=_hom->fwd[0][0]*u+_hom->fwd[0][1]*v;
  y=_hom->fwd[1][0]*u+_hom->fwd[1][1]*v;
  w=_hom->fwd[2][0]*u+_hom->fwd[2][1]*v+_hom->fwd22;
  dx=_hom->fwd[0][1]*_ul->size[1];
  dy=_hom->fwd[1][1]*_ul->size[1];
  dw=_hom->fwd[2][1]*_ul->size[1];
  for(k=i=0;;i++){
    /*Skip the timing pattern row.*/
    if(i!=6){
      qr_hom_fproject(p,_hom,x,y,w);
      lo[0]|=qr_img_get_bit(_img,_width,_height,p[0],p[1])<<k++;
      /*Don't advance q in the last iteration... we'll start the next loop from
         the current position.*/
      if(i>=8)break;
    }
    x+=dx;
    y+=dy;
    w+=dw;
  }
  hi[0]=0;
  dx=-_hom->fwd[0][0]*_ul->size[0];
  dy=-_hom->fwd[1][0]*_ul->size[0];
  dw=-_hom->fwd[2][0]*_ul->size[0];
  while(i-->0){
    x+=dx;
    y+=dy;
    w+=dw;
    /*Skip the timing pattern column.*/
    if(i!=6){
      qr_hom_fproject(p,_hom,x,y,w);
      hi[0]|=qr_img_get_bit(_img,_width,_height,p[0],p[1])<<k++;
    }
  }
  /*Read the bits next to the UR corner.*/
  lo[1]=0;
  u=_ur->o[0]+3*_ur->size[0];
  v=_ur->o[1]+5*_ur->size[1];
  x=_hom->fwd[0][0]*u+_hom->fwd[0][1]*v;
  y=_hom->fwd[1][0]*u+_hom->fwd[1][1]*v;
  w=_hom->fwd[2][0]*u+_hom->fwd[2][1]*v+_hom->fwd22;
  dx=-_hom->fwd[0][0]*_ur->size[0];
  dy=-_hom->fwd[1][0]*_ur->size[0];
  dw=-_hom->fwd[2][0]*_ur->size[0];
  for(k=0;k<8;k++){
    qr_hom_fproject(p,_hom,x,y,w);
    lo[1]|=qr_img_get_bit(_img,_width,_height,p[0],p[1])<<k;
    x+=dx;
    y+=dy;
    w+=dw;
  }
  /*Read the bits next to the DL corner.*/
  hi[1]=0;
  u=_dl->o[0]+5*_dl->size[0];
  v=_dl->o[1]-3*_dl->size[1];
  x=_hom->fwd[0][0]*u+_hom->fwd[0][1]*v;
  y=_hom->fwd[1][0]*u+_hom->fwd[1][1]*v;
  w=_hom->fwd[2][0]*u+_hom->fwd[2][1]*v+_hom->fwd22;
  dx=_hom->fwd[0][1]*_dl->size[1];
  dy=_hom->fwd[1][1]*_dl->size[1];
  dw=_hom->fwd[2][1]*_dl->size[1];
  for(k=8;k<15;k++){
    qr_hom_fproject(p,_hom,x,y,w);
    hi[1]|=qr_img_get_bit(_img,_width,_height,p[0],p[1])<<k;
    x+=dx;
    y+=dy;
    w+=dw;
  }
  /*For each group of bits we have two samples... try them in all combinations
     and pick the most popular valid code, breaking ties using the number of
     bit errors.*/
  imax=2<<(hi[0]!=hi[1]);
  di=1+(lo[0]==lo[1]);
  nfmt_info=0;
  for(i=0;i<imax;i+=di){
    unsigned v;
    int      ret;
    int      j;
    v=(lo[i&1]|hi[i>>1])^0x5412;
    ret=bch15_5_correct(&v);
    v>>=10;
    if(ret<0)ret=4;
    for(j=0;;j++){
      if(j>=nfmt_info){
        fmt_info[j]=v;
        count[j]=1;
        nerrs[j]=ret;
        nfmt_info++;
        break;
      }
      if(fmt_info[j]==(int)v){
        count[j]++;
        if(ret<nerrs[j])nerrs[j]=ret;
        break;
      }
    }
  }
  besti=0;
  for(i=1;i<nfmt_info;i++){
    if(nerrs[besti]>3&&nerrs[i]<=3||
     count[i]>count[besti]||count[i]==count[besti]&&nerrs[i]<nerrs[besti]){
      besti=i;
    }
  }
  return nerrs[besti]<4?fmt_info[besti]:-1;
}