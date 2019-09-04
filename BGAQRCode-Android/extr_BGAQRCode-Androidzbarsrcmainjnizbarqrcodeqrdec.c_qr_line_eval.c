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

__attribute__((used)) static int qr_line_eval(qr_line _line,int _x,int _y){
  return _line[0]*_x+_line[1]*_y+_line[2];
}