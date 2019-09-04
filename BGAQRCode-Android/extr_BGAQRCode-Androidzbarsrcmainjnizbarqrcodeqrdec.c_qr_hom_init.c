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
struct TYPE_3__ {int** fwd; int x0; int y0; int fwd22; int res; void* inv22; void*** inv; } ;
typedef  TYPE_1__ qr_hom ;

/* Variables and functions */
 int QR_EXTMUL (int,int,int) ; 
 void* QR_FIXMUL (int,int,int,int) ; 
 int QR_INT_BITS ; 
 int QR_MAXI (int,int) ; 
 int abs (int) ; 
 int qr_ilog (int) ; 

__attribute__((used)) static void qr_hom_init(qr_hom *_hom,int _x0,int _y0,
 int _x1,int _y1,int _x2,int _y2,int _x3,int _y3,int _res){
  int dx10;
  int dx20;
  int dx30;
  int dx31;
  int dx32;
  int dy10;
  int dy20;
  int dy30;
  int dy31;
  int dy32;
  int a20;
  int a21;
  int a22;
  int b0;
  int b1;
  int b2;
  int s1;
  int s2;
  int r1;
  int r2;
  dx10=_x1-_x0;
  dx20=_x2-_x0;
  dx30=_x3-_x0;
  dx31=_x3-_x1;
  dx32=_x3-_x2;
  dy10=_y1-_y0;
  dy20=_y2-_y0;
  dy30=_y3-_y0;
  dy31=_y3-_y1;
  dy32=_y3-_y2;
  a20=dx32*dy10-dx10*dy32;
  a21=dx20*dy31-dx31*dy20;
  a22=dx32*dy31-dx31*dy32;
  /*Figure out if we need to downscale anything.*/
  b0=qr_ilog(QR_MAXI(abs(dx10),abs(dy10)))+qr_ilog(abs(a20+a22));
  b1=qr_ilog(QR_MAXI(abs(dx20),abs(dy20)))+qr_ilog(abs(a21+a22));
  b2=qr_ilog(QR_MAXI(QR_MAXI(abs(a20),abs(a21)),abs(a22)));
  s1=QR_MAXI(0,_res+QR_MAXI(QR_MAXI(b0,b1),b2)-(QR_INT_BITS-2));
  r1=(1<<s1)>>1;
  /*Compute the final coefficients of the forward transform.
    The 32x32->64 bit multiplies are really needed for accuracy with large
     versions.*/
  _hom->fwd[0][0]=QR_FIXMUL(dx10,a20+a22,r1,s1);
  _hom->fwd[0][1]=QR_FIXMUL(dx20,a21+a22,r1,s1);
  _hom->x0=_x0;
  _hom->fwd[1][0]=QR_FIXMUL(dy10,a20+a22,r1,s1);
  _hom->fwd[1][1]=QR_FIXMUL(dy20,a21+a22,r1,s1);
  _hom->y0=_y0;
  _hom->fwd[2][0]=a20+r1>>s1;
  _hom->fwd[2][1]=a21+r1>>s1;
  _hom->fwd22=s1>_res?a22+(r1>>_res)>>s1-_res:a22<<_res-s1;
  /*Now compute the inverse transform.*/
  b0=qr_ilog(QR_MAXI(QR_MAXI(abs(dx10),abs(dx20)),abs(dx30)))+
   qr_ilog(QR_MAXI(abs(_hom->fwd[0][0]),abs(_hom->fwd[1][0])));
  b1=qr_ilog(QR_MAXI(QR_MAXI(abs(dy10),abs(dy20)),abs(dy30)))+
   qr_ilog(QR_MAXI(abs(_hom->fwd[0][1]),abs(_hom->fwd[1][1])));
  b2=qr_ilog(abs(a22))-s1;
  s2=QR_MAXI(0,QR_MAXI(b0,b1)+b2-(QR_INT_BITS-3));
  r2=(1<<s2)>>1;
  s1+=s2;
  r1<<=s2;
  /*The 32x32->64 bit multiplies are really needed for accuracy with large
     versions.*/
  _hom->inv[0][0]=QR_FIXMUL(_hom->fwd[1][1],a22,r1,s1);
  _hom->inv[0][1]=QR_FIXMUL(-_hom->fwd[0][1],a22,r1,s1);
  _hom->inv[1][0]=QR_FIXMUL(-_hom->fwd[1][0],a22,r1,s1);
  _hom->inv[1][1]=QR_FIXMUL(_hom->fwd[0][0],a22,r1,s1);
  _hom->inv[2][0]=QR_FIXMUL(_hom->fwd[1][0],_hom->fwd[2][1],
   -QR_EXTMUL(_hom->fwd[1][1],_hom->fwd[2][0],r2),s2);
  _hom->inv[2][1]=QR_FIXMUL(_hom->fwd[0][1],_hom->fwd[2][0],
   -QR_EXTMUL(_hom->fwd[0][0],_hom->fwd[2][1],r2),s2);
  _hom->inv22=QR_FIXMUL(_hom->fwd[0][0],_hom->fwd[1][1],
   -QR_EXTMUL(_hom->fwd[0][1],_hom->fwd[1][0],r2),s2);
  _hom->res=_res;
}