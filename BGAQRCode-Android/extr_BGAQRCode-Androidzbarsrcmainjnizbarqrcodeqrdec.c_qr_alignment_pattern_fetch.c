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
 int qr_img_get_bit (unsigned char const*,int,int,int,int) ; 

__attribute__((used)) static unsigned qr_alignment_pattern_fetch(qr_point _p[5][5],int _x0,int _y0,
 const unsigned char *_img,int _width,int _height){
  unsigned v;
  int      i;
  int      j;
  int      k;
  int      dx;
  int      dy;
  dx=_x0-_p[2][2][0];
  dy=_y0-_p[2][2][1];
  v=0;
  for(k=i=0;i<5;i++)for(j=0;j<5;j++,k++){
    v|=qr_img_get_bit(_img,_width,_height,_p[i][j][0]+dx,_p[i][j][1]+dy)<<k;
  }
  return v;
}