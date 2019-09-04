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
 int QR_CLAMPI (int /*<<< orphan*/ ,int,int) ; 
 int QR_FINDER_SUBPREC ; 

__attribute__((used)) static int qr_img_get_bit(const unsigned char *_img,int _width,int _height,
 int _x,int _y){
  _x>>=QR_FINDER_SUBPREC;
  _y>>=QR_FINDER_SUBPREC;
  return _img[QR_CLAMPI(0,_y,_height-1)*_width+QR_CLAMPI(0,_x,_width-1)]!=0;
}