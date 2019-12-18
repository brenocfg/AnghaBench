#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int uint16 ;
struct TYPE_6__ {int w; } ;
struct TYPE_8__ {scalar_t__ ram; TYPE_2__ dac; } ;
struct TYPE_7__ {scalar_t__* word_ram; TYPE_1__* regs; } ;
struct TYPE_5__ {int w; } ;

/* Variables and functions */
 TYPE_4__ cdc ; 
 TYPE_3__ scd ; 

void word_ram_1_dma_w(unsigned int words)
{
  uint16 data;

  /* CDC buffer source address */
  uint16 src_index = cdc.dac.w & 0x3ffe;
  
  /* WORD-RAM destination address*/
  uint32 dst_index = ((scd.regs[0x0a>>1].w << 3) & 0x1fffe);
  
  /* update DMA destination address */
  scd.regs[0x0a>>1].w += (words >> 2);

  /* update DMA source address */
  cdc.dac.w += (words << 1);

  /* DMA transfer */
  while (words--)
  {
    /* read 16-bit word from CDC buffer */
    data = *(uint16 *)(cdc.ram + src_index);

#ifdef LSB_FIRST
    /* source data is stored in big endian format */
    data = ((data >> 8) | (data << 8)) & 0xffff;
#endif

    /* write 16-bit word to WORD-RAM */
    *(uint16 *)(scd.word_ram[1] + dst_index) = data ;

    /* increment CDC buffer source address */
    src_index = (src_index + 2) & 0x3ffe;

    /* increment WORD-RAM destination address */
    dst_index = (dst_index + 2) & 0x1fffe;
  }
}