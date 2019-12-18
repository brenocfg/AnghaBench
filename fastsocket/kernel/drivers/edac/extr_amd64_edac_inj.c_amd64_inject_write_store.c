#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mem_ctl_info {struct amd64_pvt* pvt_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  bit_map; int /*<<< orphan*/  word; int /*<<< orphan*/  section; } ;
struct amd64_pvt {int /*<<< orphan*/  F3; TYPE_1__ injection; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  F10_NB_ARRAY_ADDR ; 
 int /*<<< orphan*/  F10_NB_ARRAY_DATA ; 
 int F10_NB_ARRAY_DRAM_ECC ; 
 int SET_NB_ARRAY_ADDRESS (int /*<<< orphan*/ ) ; 
 int SET_NB_DRAM_INJECTION_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd64_write_pci_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugf0 (char*,int,int) ; 
 int strict_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t amd64_inject_write_store(struct mem_ctl_info *mci,
					const char *data, size_t count)
{
	struct amd64_pvt *pvt = mci->pvt_info;
	unsigned long value;
	u32 section, word_bits;
	int ret = 0;

	ret = strict_strtoul(data, 10, &value);
	if (ret != -EINVAL) {

		/* Form value to choose 16-byte section of cacheline */
		section = F10_NB_ARRAY_DRAM_ECC |
				SET_NB_ARRAY_ADDRESS(pvt->injection.section);
		amd64_write_pci_cfg(pvt->F3, F10_NB_ARRAY_ADDR, section);

		word_bits = SET_NB_DRAM_INJECTION_WRITE(pvt->injection.word,
						pvt->injection.bit_map);

		/* Issue 'word' and 'bit' along with the READ request */
		amd64_write_pci_cfg(pvt->F3, F10_NB_ARRAY_DATA, word_bits);

		debugf0("section=0x%x word_bits=0x%x\n", section, word_bits);

		return count;
	}
	return ret;
}