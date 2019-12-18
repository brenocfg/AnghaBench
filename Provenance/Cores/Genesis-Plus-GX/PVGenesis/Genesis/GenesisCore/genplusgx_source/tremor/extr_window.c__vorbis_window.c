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
 void const* vwin1024 ; 
 void const* vwin128 ; 
 void const* vwin2048 ; 
 void const* vwin256 ; 
 void const* vwin4096 ; 
 void const* vwin512 ; 
 void const* vwin64 ; 
 void const* vwin8192 ; 

const void *_vorbis_window(int type, int left){

  switch(type){
  case 0:

    switch(left){
    case 32:
      return vwin64;
    case 64:
      return vwin128;
    case 128:
      return vwin256;
    case 256:
      return vwin512;
    case 512:
      return vwin1024;
    case 1024:
      return vwin2048;
    case 2048:
      return vwin4096;
    case 4096:
      return vwin8192;
    default:
      return(0);
    }
    break;
  default:
    return(0);
  }
}