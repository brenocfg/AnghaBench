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
struct TYPE_3__ {size_t allocsize; unsigned int* data; size_t size; } ;
typedef  TYPE_1__ uivector ;

/* Variables and functions */
 void* lodepng_realloc (unsigned int*,size_t) ; 

__attribute__((used)) static unsigned uivector_resize(uivector* p, size_t size)
{
  if(size * sizeof(unsigned) > p->allocsize)
  {
    size_t newsize = size * sizeof(unsigned) * 2;
    void* data = lodepng_realloc(p->data, newsize);
    if(data)
    {
      p->allocsize = newsize;
      p->data = (unsigned*)data;
      p->size = size;
    }
    else return 0;
  }
  else p->size = size;
  return 1;
}