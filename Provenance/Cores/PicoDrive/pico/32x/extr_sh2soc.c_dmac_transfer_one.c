#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct dma_chan {int chcr; int sar; int dar; scalar_t__ tcr; } ;
typedef  int /*<<< orphan*/  SH2 ;

/* Variables and functions */
 int p32x_sh2_read16 (int,int /*<<< orphan*/ *) ; 
 int p32x_sh2_read32 (int,int /*<<< orphan*/ *) ; 
 int p32x_sh2_read8 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p32x_sh2_write16 (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p32x_sh2_write32 (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p32x_sh2_write8 (int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dmac_transfer_one(SH2 *sh2, struct dma_chan *chan)
{
  u32 size, d;

  size = (chan->chcr >> 10) & 3;
  switch (size) {
  case 0:
    d = p32x_sh2_read8(chan->sar, sh2);
    p32x_sh2_write8(chan->dar, d, sh2);
  case 1:
    d = p32x_sh2_read16(chan->sar, sh2);
    p32x_sh2_write16(chan->dar, d, sh2);
    break;
  case 2:
    d = p32x_sh2_read32(chan->sar, sh2);
    p32x_sh2_write32(chan->dar, d, sh2);
    break;
  case 3:
    d = p32x_sh2_read32(chan->sar + 0x00, sh2);
    p32x_sh2_write32(chan->dar + 0x00, d, sh2);
    d = p32x_sh2_read32(chan->sar + 0x04, sh2);
    p32x_sh2_write32(chan->dar + 0x04, d, sh2);
    d = p32x_sh2_read32(chan->sar + 0x08, sh2);
    p32x_sh2_write32(chan->dar + 0x08, d, sh2);
    d = p32x_sh2_read32(chan->sar + 0x0c, sh2);
    p32x_sh2_write32(chan->dar + 0x0c, d, sh2);
    chan->sar += 16; // always?
    if (chan->chcr & (1 << 15))
      chan->dar -= 16;
    if (chan->chcr & (1 << 14))
      chan->dar += 16;
    chan->tcr -= 4;
    return;
  }
  chan->tcr--;

  size = 1 << size;
  if (chan->chcr & (1 << 15))
    chan->dar -= size;
  if (chan->chcr & (1 << 14))
    chan->dar += size;
  if (chan->chcr & (1 << 13))
    chan->sar -= size;
  if (chan->chcr & (1 << 12))
    chan->sar += size;
}