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
struct TYPE_3__ {unsigned char* img_buffer; unsigned char* img_buffer_original; unsigned char* img_buffer_end; } ;
typedef  TYPE_1__ rbmp_context ;

/* Variables and functions */
 unsigned char* rbmp_bmp_load (TYPE_1__*,unsigned int*,unsigned int*,int*,int) ; 

__attribute__((used)) static unsigned char *rbmp_load_from_memory(unsigned char const *buffer, int len,
      unsigned *x, unsigned *y, int *comp, int req_comp)
{
   rbmp_context s;

   s.img_buffer          = (unsigned char*)buffer;
   s.img_buffer_original = (unsigned char*)buffer;
   s.img_buffer_end      = (unsigned char*)buffer+len;

   return rbmp_bmp_load(&s,x,y,comp,req_comp);
}