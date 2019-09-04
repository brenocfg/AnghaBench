#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int* qr_point ;
struct TYPE_6__ {int** fwd; int fwd22; } ;
typedef  TYPE_1__ qr_hom ;
struct TYPE_7__ {int* o; int* size; } ;
typedef  TYPE_2__ qr_finder ;

/* Variables and functions */
 int bch18_6_correct (unsigned int*) ; 
 int /*<<< orphan*/  qr_hom_fproject (int*,TYPE_1__ const*,int,int,int) ; 
 int qr_img_get_bit (unsigned char const*,int,int,int,int) ; 

__attribute__((used)) static int qr_finder_version_decode(qr_finder *_f,const qr_hom *_hom,
 const unsigned char *_img,int _width,int _height,int _dir){
  qr_point q;
  unsigned v;
  int      x0;
  int      y0;
  int      w0;
  int      dxi;
  int      dyi;
  int      dwi;
  int      dxj;
  int      dyj;
  int      dwj;
  int      ret;
  int      i;
  int      j;
  int      k;
  v=0;
  q[_dir]=_f->o[_dir]-7*_f->size[_dir];
  q[1-_dir]=_f->o[1-_dir]-3*_f->size[1-_dir];
  x0=_hom->fwd[0][0]*q[0]+_hom->fwd[0][1]*q[1];
  y0=_hom->fwd[1][0]*q[0]+_hom->fwd[1][1]*q[1];
  w0=_hom->fwd[2][0]*q[0]+_hom->fwd[2][1]*q[1]+_hom->fwd22;
  dxi=_hom->fwd[0][1-_dir]*_f->size[1-_dir];
  dyi=_hom->fwd[1][1-_dir]*_f->size[1-_dir];
  dwi=_hom->fwd[2][1-_dir]*_f->size[1-_dir];
  dxj=_hom->fwd[0][_dir]*_f->size[_dir];
  dyj=_hom->fwd[1][_dir]*_f->size[_dir];
  dwj=_hom->fwd[2][_dir]*_f->size[_dir];
  for(k=i=0;i<6;i++){
    int x;
    int y;
    int w;
    x=x0;
    y=y0;
    w=w0;
    for(j=0;j<3;j++,k++){
      qr_point p;
      qr_hom_fproject(p,_hom,x,y,w);
      v|=qr_img_get_bit(_img,_width,_height,p[0],p[1])<<k;
      x+=dxj;
      y+=dyj;
      w+=dwj;
    }
    x0+=dxi;
    y0+=dyi;
    w0+=dwi;
  }
  ret=bch18_6_correct(&v);
  /*TODO: I seem to have an image with the version bits in a different order
     (the transpose of the standard order).
    Even if I change the order here so I can parse the version on this image,
     I can't decode the rest of the code.
    If this is really needed, we should just re-order the bits.*/
#if 0
  if(ret<0){
    /*17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
       0  3  6  9 12 15  1  4  7 10 13 16  2  5  8 11 14 17
      17 13  9  5  1 -3 10  6  2 -2 -6-10  3 -1 -5 -9-13-17*/
    v=0;
    for(k=i=0;i<3;i++){
      p[_dir]=_f->o[_dir]+_f->size[_dir]*(-5-i);
      for(j=0;j<6;j++,k++){
        qr_point q;
        p[1-_dir]=_f->o[1-_dir]+_f->size[1-_dir]*(2-j);
        qr_hom_project(q,_hom,p[0],p[1]);
        v|=qr_img_get_bit(_img,_width,_height,q[0],q[1])<<k;
      }
    }
    ret=bch18_6_correct(&v);
  }
#endif
  return ret>=0?(int)(v>>12):ret;
}