#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int* qr_line ;

/* Variables and functions */
 int QR_MAXI (int,int) ; 
 int abs (int) ; 
 int qr_ihypot (int,int) ; 
 int qr_ilog (int) ; 

__attribute__((used)) static void qr_line_fit(qr_line _l,int _x0,int _y0,
 int _sxx,int _sxy,int _syy,int _res){
  int dshift;
  int dround;
  int u;
  int v;
  int w;
  u=abs(_sxx-_syy);
  v=-_sxy<<1;
  w=qr_ihypot(u,v);
  /*Computations in later stages can easily overflow with moderate sizes, so we
     compute a shift factor to scale things down into a managable range.
    We ensure that the product of any two of _l[0] and _l[1] fits within _res
     bits, which allows computation of line intersections without overflow.*/
  dshift=QR_MAXI(0,QR_MAXI(qr_ilog(u),qr_ilog(abs(v)))+1-(_res+1>>1));
  dround=(1<<dshift)>>1;
  if(_sxx>_syy){
    _l[0]=v+dround>>dshift;
    _l[1]=u+w+dround>>dshift;
  }
  else{
    _l[0]=u+w+dround>>dshift;
    _l[1]=v+dround>>dshift;
  }
  _l[2]=-(_x0*_l[0]+_y0*_l[1]);
}