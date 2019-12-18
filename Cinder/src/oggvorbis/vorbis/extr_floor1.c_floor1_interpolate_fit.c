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
struct TYPE_3__ {long posts; } ;
typedef  TYPE_1__ vorbis_look_floor1 ;
typedef  int /*<<< orphan*/  vorbis_block ;

/* Variables and functions */
 int* _vorbis_block_alloc (int /*<<< orphan*/ *,int) ; 

int *floor1_interpolate_fit(vorbis_block *vb,vorbis_look_floor1 *look,
                          int *A,int *B,
                          int del){

  long i;
  long posts=look->posts;
  int *output=NULL;

  if(A && B){
    output=_vorbis_block_alloc(vb,sizeof(*output)*posts);

    /* overly simpleminded--- look again post 1.2 */
    for(i=0;i<posts;i++){
      output[i]=((65536-del)*(A[i]&0x7fff)+del*(B[i]&0x7fff)+32768)>>16;
      if(A[i]&0x8000 && B[i]&0x8000)output[i]|=0x8000;
    }
  }

  return(output);
}