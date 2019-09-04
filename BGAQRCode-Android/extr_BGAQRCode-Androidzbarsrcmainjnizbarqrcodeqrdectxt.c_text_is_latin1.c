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

__attribute__((used)) static int text_is_latin1(const unsigned char *_text,int _len){
  int i;
  for(i=0;i<_len;i++){
    /*The following line fails to compile correctly with gcc 3.4.4 on ARM with
       any optimizations enabled.*/
    if(_text[i]>=0x80&&_text[i]<0xA0)return 0;
  }
  return 1;
}