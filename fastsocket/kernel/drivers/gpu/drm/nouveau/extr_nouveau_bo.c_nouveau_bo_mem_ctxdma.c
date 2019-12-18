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
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_mem_reg {scalar_t__ mem_type; } ;
struct ttm_buffer_object {int dummy; } ;
struct nouveau_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NvDmaFB ; 
 int /*<<< orphan*/  NvDmaTT ; 
 scalar_t__ TTM_PL_TT ; 

__attribute__((used)) static inline uint32_t
nouveau_bo_mem_ctxdma(struct ttm_buffer_object *bo,
		      struct nouveau_channel *chan, struct ttm_mem_reg *mem)
{
	if (mem->mem_type == TTM_PL_TT)
		return NvDmaTT;
	return NvDmaFB;
}