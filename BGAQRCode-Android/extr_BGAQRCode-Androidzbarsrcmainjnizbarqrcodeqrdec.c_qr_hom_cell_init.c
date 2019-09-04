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
struct TYPE_3__ {int** fwd; int x0; int y0; int u0; int v0; } ;
typedef  TYPE_1__ qr_hom_cell ;

/* Variables and functions */
 int QR_ALIGN_SUBPREC ; 
 int QR_DIVROUND (int,int) ; 
 int QR_FIXMUL (int,int,int,int) ; 
 int QR_FLIPSIGNI (int,int) ; 
 int QR_INT_BITS ; 
 int QR_MAXI (int,int) ; 
 int abs (int) ; 
 int qr_ilog (int) ; 

__attribute__((used)) static void qr_hom_cell_init(qr_hom_cell *_cell,int _u0,int _v0,
 int _u1,int _v1,int _u2,int _v2,int _u3,int _v3,int _x0,int _y0,
 int _x1,int _y1,int _x2,int _y2,int _x3,int _y3){
  int du10;
  int du20;
  int du30;
  int du31;
  int du32;
  int dv10;
  int dv20;
  int dv30;
  int dv31;
  int dv32;
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
  int a00;
  int a01;
  int a02;
  int a10;
  int a11;
  int a12;
  int a20;
  int a21;
  int a22;
  int i00;
  int i01;
  int i10;
  int i11;
  int i20;
  int i21;
  int i22;
  int b0;
  int b1;
  int b2;
  int shift;
  int round;
  int x;
  int y;
  int w;
  /*First, correct for the arrangement of the source points.
    We take advantage of the fact that we know the source points have a very
     limited dynamic range (so there will never be overflow) and a small amount
     of projective distortion.*/
  du10=_u1-_u0;
  du20=_u2-_u0;
  du30=_u3-_u0;
  du31=_u3-_u1;
  du32=_u3-_u2;
  dv10=_v1-_v0;
  dv20=_v2-_v0;
  dv30=_v3-_v0;
  dv31=_v3-_v1;
  dv32=_v3-_v2;
  /*Compute the coefficients of the forward transform from the unit square to
     the source point configuration.*/
  a20=du32*dv10-du10*dv32;
  a21=du20*dv31-du31*dv20;
  if(a20||a21)a22=du32*dv31-du31*dv32;
  /*If the source grid points aren't in a non-affine arrangement, there's no
     reason to scale everything by du32*dv31-du31*dv32.
    Not doing so allows a much larger dynamic range, and is the only way we can
     initialize a base cell that covers the whole grid.*/
  else a22=1;
  a00=du10*(a20+a22);
  a01=du20*(a21+a22);
  a10=dv10*(a20+a22);
  a11=dv20*(a21+a22);
  /*Now compute the inverse transform.*/
  i00=a11*a22;
  i01=-a01*a22;
  i10=-a10*a22;
  i11=a00*a22;
  i20=a10*a21-a11*a20;
  i21=a01*a20-a00*a21;
  i22=a00*a11-a01*a10;
  /*Invert the coefficients.
    Since i22 is the largest, we divide it by all the others.
    The quotient is often exact (e.g., when the source points contain no
     projective distortion), and is never zero.
    Hence we can use zero to signal "infinity" when the divisor is zero.*/
  if(i00)i00=QR_FLIPSIGNI(QR_DIVROUND(i22,abs(i00)),i00);
  if(i01)i01=QR_FLIPSIGNI(QR_DIVROUND(i22,abs(i01)),i01);
  if(i10)i10=QR_FLIPSIGNI(QR_DIVROUND(i22,abs(i10)),i10);
  if(i11)i11=QR_FLIPSIGNI(QR_DIVROUND(i22,abs(i11)),i11);
  if(i20)i20=QR_FLIPSIGNI(QR_DIVROUND(i22,abs(i20)),i20);
  if(i21)i21=QR_FLIPSIGNI(QR_DIVROUND(i22,abs(i21)),i21);
  /*Now compute the map from the unit square into the image.*/
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
  shift=QR_MAXI(0,QR_MAXI(QR_MAXI(b0,b1),b2)-(QR_INT_BITS-3-QR_ALIGN_SUBPREC));
  round=(1<<shift)>>1;
  /*Compute the final coefficients of the forward transform.*/
  a00=QR_FIXMUL(dx10,a20+a22,round,shift);
  a01=QR_FIXMUL(dx20,a21+a22,round,shift);
  a10=QR_FIXMUL(dy10,a20+a22,round,shift);
  a11=QR_FIXMUL(dy20,a21+a22,round,shift);
  /*And compose the two transforms.
    Since we inverted the coefficients above, we divide by them here instead
     of multiplying.
    This lets us take advantage of the full dynamic range.
    Note a zero divisor is really "infinity", and thus the quotient should also
     be zero.*/
  _cell->fwd[0][0]=(i00?QR_DIVROUND(a00,i00):0)+(i10?QR_DIVROUND(a01,i10):0);
  _cell->fwd[0][1]=(i01?QR_DIVROUND(a00,i01):0)+(i11?QR_DIVROUND(a01,i11):0);
  _cell->fwd[1][0]=(i00?QR_DIVROUND(a10,i00):0)+(i10?QR_DIVROUND(a11,i10):0);
  _cell->fwd[1][1]=(i01?QR_DIVROUND(a10,i01):0)+(i11?QR_DIVROUND(a11,i11):0);
  _cell->fwd[2][0]=(i00?QR_DIVROUND(a20,i00):0)+(i10?QR_DIVROUND(a21,i10):0)
   +(i20?QR_DIVROUND(a22,i20):0)+round>>shift;
  _cell->fwd[2][1]=(i01?QR_DIVROUND(a20,i01):0)+(i11?QR_DIVROUND(a21,i11):0)
   +(i21?QR_DIVROUND(a22,i21):0)+round>>shift;
  _cell->fwd[2][2]=a22+round>>shift;
  /*Mathematically, a02 and a12 are exactly zero.
    However, that concentrates all of the rounding error in the (_u3,_v3)
     corner; we compute offsets which distribute it over the whole range.*/
  x=_cell->fwd[0][0]*du10+_cell->fwd[0][1]*dv10;
  y=_cell->fwd[1][0]*du10+_cell->fwd[1][1]*dv10;
  w=_cell->fwd[2][0]*du10+_cell->fwd[2][1]*dv10+_cell->fwd[2][2];
  a02=dx10*w-x;
  a12=dy10*w-y;
  x=_cell->fwd[0][0]*du20+_cell->fwd[0][1]*dv20;
  y=_cell->fwd[1][0]*du20+_cell->fwd[1][1]*dv20;
  w=_cell->fwd[2][0]*du20+_cell->fwd[2][1]*dv20+_cell->fwd[2][2];
  a02+=dx20*w-x;
  a12+=dy20*w-y;
  x=_cell->fwd[0][0]*du30+_cell->fwd[0][1]*dv30;
  y=_cell->fwd[1][0]*du30+_cell->fwd[1][1]*dv30;
  w=_cell->fwd[2][0]*du30+_cell->fwd[2][1]*dv30+_cell->fwd[2][2];
  a02+=dx30*w-x;
  a12+=dy30*w-y;
  _cell->fwd[0][2]=a02+2>>2;
  _cell->fwd[1][2]=a12+2>>2;
  _cell->x0=_x0;
  _cell->y0=_y0;
  _cell->u0=_u0;
  _cell->v0=_v0;
}