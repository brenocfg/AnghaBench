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
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ DMA_CHNL (int,int) ; 
 scalar_t__ S6_DMA_CMONCHUNK ; 
 scalar_t__ S6_DMA_DSTSKIP ; 
 scalar_t__ S6_DMA_SRCSKIP ; 
 int /*<<< orphan*/  flush_dcache_unaligned (int,int) ; 
 int /*<<< orphan*/  invalidate_dcache_unaligned (int,int) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  s6dmac_put_fifo (int,int,int,int,int) ; 
 scalar_t__ xtensa_need_flush_dma_source (int) ; 
 scalar_t__ xtensa_need_invalidate_dma_destination (int) ; 

void s6dmac_put_fifo_cache(u32 dmac, int chan, u32 src, u32 dst, u32 size)
{
	if (xtensa_need_flush_dma_source(src)) {
		u32 base = src;
		u32 span = size;
		u32 chunk = readl(DMA_CHNL(dmac, chan) + S6_DMA_CMONCHUNK);
		if (chunk && (size > chunk)) {
			s32 skip =
				readl(DMA_CHNL(dmac, chan) + S6_DMA_SRCSKIP);
			u32 gaps = (size+chunk-1)/chunk - 1;
			if (skip >= 0) {
				span += gaps * skip;
			} else if (-skip > chunk) {
				s32 decr = gaps * (chunk + skip);
				base += decr;
				span = chunk - decr;
			} else {
				span = max(span + gaps * skip,
					(chunk + skip) * gaps - skip);
			}
		}
		flush_dcache_unaligned(base, span);
	}
	if (xtensa_need_invalidate_dma_destination(dst)) {
		u32 base = dst;
		u32 span = size;
		u32 chunk = readl(DMA_CHNL(dmac, chan) + S6_DMA_CMONCHUNK);
		if (chunk && (size > chunk)) {
			s32 skip =
				readl(DMA_CHNL(dmac, chan) + S6_DMA_DSTSKIP);
			u32 gaps = (size+chunk-1)/chunk - 1;
			if (skip >= 0) {
				span += gaps * skip;
			} else if (-skip > chunk) {
				s32 decr = gaps * (chunk + skip);
				base += decr;
				span = chunk - decr;
			} else {
				span = max(span + gaps * skip,
					(chunk + skip) * gaps - skip);
			}
		}
		invalidate_dcache_unaligned(base, span);
	}
	s6dmac_put_fifo(dmac, chan, src, dst, size);
}