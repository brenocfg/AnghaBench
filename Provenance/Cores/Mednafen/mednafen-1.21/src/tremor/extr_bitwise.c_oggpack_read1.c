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
struct TYPE_3__ {scalar_t__ endbyte; scalar_t__ storage; int* ptr; int endbit; } ;
typedef  TYPE_1__ oggpack_buffer ;

/* Variables and functions */

long oggpack_read1(oggpack_buffer *b){
  long ret;

  if(b->endbyte >= b->storage) goto overflow;
  ret=(b->ptr[0]>>b->endbit)&1;

  b->endbit++;
  if(b->endbit>7){
    b->endbit=0;
    b->ptr++;
    b->endbyte++;
  }
  return ret;

 overflow:
  b->ptr=NULL;
  b->endbyte=b->storage;
  b->endbit=1;
  return -1L;
}