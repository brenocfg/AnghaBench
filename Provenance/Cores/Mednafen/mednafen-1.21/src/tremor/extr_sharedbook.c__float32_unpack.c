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
typedef  long ogg_int32_t ;

/* Variables and functions */
 long VQ_FEXP_BIAS ; 
 long VQ_FMAN ; 

__attribute__((used)) static ogg_int32_t _float32_unpack(long val,int *point){
  long   mant=val&0x1fffff;
  int    sign=val&0x80000000;
  long   exp =(val&0x7fe00000L)>>VQ_FMAN;

  exp-=(VQ_FMAN-1)+VQ_FEXP_BIAS;

  if(mant){
    while(!(mant&0x40000000)){
      mant<<=1;
      exp-=1;
    }

    if(sign)mant= -mant;
  }else{
    sign=0;
    exp=-9999;
  }

  *point=exp;
  return mant;
}