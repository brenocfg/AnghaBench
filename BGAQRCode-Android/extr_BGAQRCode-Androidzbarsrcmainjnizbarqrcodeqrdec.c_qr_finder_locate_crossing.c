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
typedef  int* qr_point ;

/* Variables and functions */
 int QR_FINDER_SUBPREC ; 
 int abs (int) ; 

__attribute__((used)) static int qr_finder_locate_crossing(const unsigned char *_img,
 int _width,int _height,int _x0,int _y0,int _x1,int _y1,int _v,qr_point _p){
  qr_point x0;
  qr_point x1;
  qr_point dx;
  int      step[2];
  int      steep;
  int      err;
  int      derr;
  /*Use Bresenham's algorithm to trace along the line and find the exact
     transitions from !_v to _v and back.*/
  x0[0]=_x0;
  x0[1]=_y0;
  x1[0]=_x1;
  x1[1]=_y1;
  dx[0]=abs(_x1-_x0);
  dx[1]=abs(_y1-_y0);
  steep=dx[1]>dx[0];
  err=0;
  derr=dx[1-steep];
  step[0]=((_x0<_x1)<<1)-1;
  step[1]=((_y0<_y1)<<1)-1;
  /*Find the first crossing from !_v to _v.*/
  for(;;){
    /*If we make it all the way to the other side, there's no crossing.*/
    if(x0[steep]==x1[steep])return -1;
    x0[steep]+=step[steep];
    err+=derr;
    if(err<<1>dx[steep]){
      x0[1-steep]+=step[1-steep];
      err-=dx[steep];
    }
    if(!_img[x0[1]*_width+x0[0]]!=_v)break;
  }
  /*Find the last crossing from _v to !_v.*/
  err=0;
  for(;;){
    if(x0[steep]==x1[steep])break;
    x1[steep]-=step[steep];
    err+=derr;
    if(err<<1>dx[steep]){
      x1[1-steep]-=step[1-steep];
      err-=dx[steep];
    }
    if(!_img[x1[1]*_width+x1[0]]!=_v)break;
  }
  /*Return the midpoint of the _v segment.*/
  _p[0]=(x0[0]+x1[0]+1<<QR_FINDER_SUBPREC)>>1;
  _p[1]=(x0[1]+x1[1]+1<<QR_FINDER_SUBPREC)>>1;
  return 0;
}