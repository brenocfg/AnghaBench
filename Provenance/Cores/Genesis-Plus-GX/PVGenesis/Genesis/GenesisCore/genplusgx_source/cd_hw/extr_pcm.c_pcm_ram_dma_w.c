#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
struct TYPE_7__ {int w; } ;
struct TYPE_10__ {scalar_t__ ram; TYPE_2__ dac; } ;
struct TYPE_9__ {scalar_t__ bank; } ;
struct TYPE_8__ {TYPE_1__* regs; } ;
struct TYPE_6__ {int w; } ;

/* Variables and functions */
 TYPE_5__ cdc ; 
 TYPE_4__ pcm ; 
 TYPE_3__ scd ; 

void pcm_ram_dma_w(unsigned int words)
{
  uint16 data;

  /* CDC buffer source address */
  uint16 src_index = cdc.dac.w & 0x3ffe;
  
  /* PCM-RAM destination address*/
  uint16 dst_index = (scd.regs[0x0a>>1].w << 2) & 0xffe;
  
  /* update DMA destination address */
  scd.regs[0x0a>>1].w += (words >> 1);

  /* update DMA source address */
  cdc.dac.w += (words << 1);

  /* DMA transfer */
  while (words--)
  {
    /* read 16-bit word from CDC buffer */
    data = *(uint16 *)(cdc.ram + src_index);

    /* write 16-bit word to PCM RAM (endianness does not matter since PCM RAM is always accessed as byte)*/
    *(uint16 *)(pcm.bank + dst_index) = data ;

    /* increment CDC buffer source address */
    src_index = (src_index + 2) & 0x3ffe;

    /* increment PCM-RAM destination address */
    dst_index = (dst_index + 2) & 0xffe;
  }
}