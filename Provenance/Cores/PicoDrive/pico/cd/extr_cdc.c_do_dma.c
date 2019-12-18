#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  enum dma_type { ____Placeholder_dma_type } dma_type ;
struct TYPE_4__ {size_t bank; } ;
struct TYPE_6__ {int* s68k_regs; int /*<<< orphan*/  word_ram2M; int /*<<< orphan*/ * word_ram1M; int /*<<< orphan*/  prg_ram; TYPE_1__ pcm; int /*<<< orphan*/ ** pcm_ram_b; } ;
struct TYPE_5__ {int dac; scalar_t__ ram; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_ANOMALY ; 
 int /*<<< orphan*/  EL_CD ; 
 TYPE_3__* Pico_mcd ; 
 TYPE_2__ cdc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy16bswap (void*,scalar_t__,int) ; 
#define  pcm_ram_dma_w 132 
#define  prg_ram_dma_w 131 
#define  word_ram_0_dma_w 130 
#define  word_ram_1_dma_w 129 
#define  word_ram_2M_dma_w 128 

__attribute__((used)) static void do_dma(enum dma_type type, int words_in)
{
	int dma_addr = (Pico_mcd->s68k_regs[0x0a] << 8) | Pico_mcd->s68k_regs[0x0b];
  int src_addr = cdc.dac & 0x3ffe;
  int dst_addr = dma_addr;
  int words = words_in;
  int dst_limit = 0;
  uint8 *dst;
  int len;

  elprintf(EL_CD, "dma %d %04x->%04x %x",
    type, cdc.dac, dst_addr, words_in);

  switch (type)
  {
    case pcm_ram_dma_w:
      dst_addr = (dst_addr << 2) & 0xffc;
      if (dst_addr + words * 2 > 0x1000) {
        elprintf(EL_ANOMALY, "pcm dma oflow: %x %x", dst_addr, words);
        words = (0x1000 - dst_addr) / 2;
      }
      dst = Pico_mcd->pcm_ram_b[Pico_mcd->pcm.bank];
      dst = dst + dst_addr;
      while (words > 0)
      {
        if (src_addr + words * 2 > 0x4000) {
          len = 0x4000 - src_addr;
          memcpy(dst, cdc.ram + src_addr, len);
          dst += len;
          src_addr = 0;
          words -= len / 2;
          continue;
        }
        memcpy(dst, cdc.ram + src_addr, words * 2);
        break;
      }
      goto update_dma;

    case prg_ram_dma_w:
      dst_addr <<= 3;
		  dst = Pico_mcd->prg_ram + dst_addr;
      dst_limit = 0x80000;
      break;

    case word_ram_0_dma_w:
      dst_addr = (dst_addr << 3) & 0x1fffe;
			dst = Pico_mcd->word_ram1M[0] + dst_addr;
      dst_limit = 0x20000;
      break;

    case word_ram_1_dma_w:
      dst_addr = (dst_addr << 3) & 0x1fffe;
			dst = Pico_mcd->word_ram1M[1] + dst_addr;
      dst_limit = 0x20000;
      break;

    case word_ram_2M_dma_w:
      dst_addr = (dst_addr << 3) & 0x3fffe;
			dst = Pico_mcd->word_ram2M + dst_addr;
      dst_limit = 0x40000;
      break;

    default:
      elprintf(EL_ANOMALY, "invalid dma: %d", type);
      goto update_dma;
  }

  if (dst_addr + words * 2 > dst_limit) {
    elprintf(EL_ANOMALY, "cd dma %d oflow: %x %x", type, dst_addr, words);
    words = (dst_limit - dst_addr) / 2;
  }
  while (words > 0)
  {
    if (src_addr + words * 2 > 0x4000) {
      len = 0x4000 - src_addr;
      memcpy16bswap((void *)dst, cdc.ram + src_addr, len / 2);
      dst += len;
      src_addr = 0;
      words -= len / 2;
      continue;
    }
    memcpy16bswap((void *)dst, cdc.ram + src_addr, words);
    break;
  }

update_dma:
  /* update DMA addresses */
  cdc.dac += words_in * 2;
  if (type == pcm_ram_dma_w)
    dma_addr += words_in >> 1;
  else
    dma_addr += words_in >> 2;

  Pico_mcd->s68k_regs[0x0a] = dma_addr >> 8;
  Pico_mcd->s68k_regs[0x0b] = dma_addr;
}