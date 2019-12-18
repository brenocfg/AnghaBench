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
struct kpcdata {int configc; unsigned long long* configv; int counterc; unsigned long long* counterv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_DATA (int /*<<< orphan*/ ,unsigned long long,int,unsigned long long,int) ; 
 int /*<<< orphan*/  PERF_KPC_CFG_REG ; 
 int /*<<< orphan*/  PERF_KPC_CFG_REG32 ; 

__attribute__((used)) static void
kperf_kpc_log(uint32_t code, uint32_t code32, const struct kpcdata *kpcd)
{
	unsigned i;

#if __LP64__
	(void)code32;
	/* config registers */
	for (i = 0; i < ((kpcd->configc + 3) / 4); i++) {
		BUF_DATA(PERF_KPC_CFG_REG,
		         kpcd->configv[0 + i * 4],
		         kpcd->configv[1 + i * 4],
		         kpcd->configv[2 + i * 4],
		         kpcd->configv[3 + i * 4]);
	}

	/* and the actual counts with one 64-bit argument each */
	for (i = 0; i < ((kpcd->counterc + 3) / 4); i++) {
		BUF_DATA(code,
		         kpcd->counterv[0 + i * 4],
		         kpcd->counterv[1 + i * 4],
		         kpcd->counterv[2 + i * 4],
		         kpcd->counterv[3 + i * 4]);
	}
#else
	(void)code;
	/* config registers */
	for (i = 0; i < ((kpcd->configc + 1) / 2); i++) {
		BUF_DATA(PERF_KPC_CFG_REG32,
		         (kpcd->configv[0 + i * 2] >> 32ULL),
		         kpcd->configv[0 + i * 2] & 0xffffffffULL,
		         (kpcd->configv[1 + i * 2] >> 32ULL),
		         kpcd->configv[1 + i * 2] & 0xffffffffULL);
	}

	/* and the actual counts with two 32-bit trace arguments each */
	for (i = 0; i < ((kpcd->counterc + 1) / 2); i++) {
		BUF_DATA(code32,
		         (kpcd->counterv[0 + i * 2] >> 32ULL),
		         kpcd->counterv[0 + i * 2] & 0xffffffffULL,
		         (kpcd->counterv[1 + i * 2] >> 32ULL),
		         kpcd->counterv[1 + i * 2] & 0xffffffffULL);
	}
#endif
}