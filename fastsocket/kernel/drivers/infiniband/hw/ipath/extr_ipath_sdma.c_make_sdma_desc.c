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
typedef  int u64 ;
struct ipath_devdata {unsigned long long ipath_sdma_generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static inline void make_sdma_desc(struct ipath_devdata *dd,
	u64 *sdmadesc, u64 addr, u64 dwlen, u64 dwoffset)
{
	WARN_ON(addr & 3);
	/* SDmaPhyAddr[47:32] */
	sdmadesc[1] = addr >> 32;
	/* SDmaPhyAddr[31:0] */
	sdmadesc[0] = (addr & 0xfffffffcULL) << 32;
	/* SDmaGeneration[1:0] */
	sdmadesc[0] |= (dd->ipath_sdma_generation & 3ULL) << 30;
	/* SDmaDwordCount[10:0] */
	sdmadesc[0] |= (dwlen & 0x7ffULL) << 16;
	/* SDmaBufOffset[12:2] */
	sdmadesc[0] |= dwoffset & 0x7ffULL;
}