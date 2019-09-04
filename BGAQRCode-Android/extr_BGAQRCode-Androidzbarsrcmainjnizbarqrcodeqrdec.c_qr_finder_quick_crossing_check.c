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

/* Variables and functions */

__attribute__((used)) static int qr_finder_quick_crossing_check(const unsigned char *_img,
 int _width,int _height,int _x0,int _y0,int _x1,int _y1,int _v){
  /*The points must be inside the image, and have a !_v:_v:!_v pattern.
    We don't scan the whole line initially, but quickly reject if the endpoints
     aren't !_v, or the midpoint isn't _v.
    If either end point is out of the image, or we don't encounter a _v pixel,
     we return a negative value, indicating the region should be considered
     empty.
    Otherwise, we return a positive value to indicate it is non-empty.*/
  if(_x0<0||_x0>=_width||_y0<0||_y0>=_height||
   _x1<0||_x1>=_width||_y1<0||_y1>=_height){
    return -1;
  }
  if(!_img[_y0*_width+_x0]!=_v||!_img[_y1*_width+_x1]!=_v)return 1;
  if(!_img[(_y0+_y1>>1)*_width+(_x0+_x1>>1)]==_v)return -1;
  return 0;
}