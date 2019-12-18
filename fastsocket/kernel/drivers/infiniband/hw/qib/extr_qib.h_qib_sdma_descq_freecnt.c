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
typedef  scalar_t__ u16 ;
struct qib_pportdata {scalar_t__ sdma_descq_removed; scalar_t__ sdma_descq_added; scalar_t__ sdma_descq_cnt; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 qib_sdma_descq_freecnt(const struct qib_pportdata *ppd)
{
	return ppd->sdma_descq_cnt -
		(ppd->sdma_descq_added - ppd->sdma_descq_removed) - 1;
}