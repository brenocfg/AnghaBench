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
struct TYPE_3__ {long endbit; long endbyte; int /*<<< orphan*/ * ptr; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ oggpack_buffer ;

/* Variables and functions */
 int /*<<< orphan*/ * mask8B ; 

void oggpackB_writetrunc(oggpack_buffer *b,long bits){
  long bytes=bits>>3;
  if(b->ptr){
    bits-=bytes*8;
    b->ptr=b->buffer+bytes;
    b->endbit=bits;
    b->endbyte=bytes;
    *b->ptr&=mask8B[bits];
  }
}