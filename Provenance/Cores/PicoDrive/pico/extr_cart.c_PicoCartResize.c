#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* rom; } ;

/* Variables and functions */
 TYPE_1__ Pico ; 
 void* plat_mremap (void*,int,int) ; 
 int rom_alloc_size ; 

int PicoCartResize(int newsize)
{
  void *tmp = plat_mremap(Pico.rom, rom_alloc_size, newsize);
  if (tmp == NULL)
    return -1;

  Pico.rom = tmp;
  rom_alloc_size = newsize;
  return 0;
}