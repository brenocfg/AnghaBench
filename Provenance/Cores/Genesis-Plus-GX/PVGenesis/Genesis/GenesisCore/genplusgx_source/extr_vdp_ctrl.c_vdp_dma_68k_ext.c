#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {TYPE_1__* memory_map; } ;
struct TYPE_3__ {scalar_t__ base; int /*<<< orphan*/  (* read16 ) (int) ;} ;

/* Variables and functions */
 int dma_src ; 
 TYPE_2__ m68k ; 
 int* reg ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  vdp_bus_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdp_dma_68k_ext(unsigned int length)
{
  uint16 data;

  /* 68k bus source address */
  uint32 source = (reg[23] << 17) | (dma_src << 1);

  do
  {
    /* Read data word from 68k bus */
    if (m68k.memory_map[source>>16].read16)
    {
      data = m68k.memory_map[source>>16].read16(source);
    }
    else
    {
      data = *(uint16 *)(m68k.memory_map[source>>16].base + (source & 0xFFFF));
    }
 
    /* Increment source address */
    source += 2;

    /* 128k DMA window */
    source = (reg[23] << 17) | (source & 0x1FFFF);

    /* Write data word to VRAM, CRAM or VSRAM */
    vdp_bus_w(data);
  }
  while (--length);

  /* Update DMA source address */
  dma_src = (source >> 1) & 0xffff;
}