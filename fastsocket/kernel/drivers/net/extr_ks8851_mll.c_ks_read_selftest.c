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
struct ks_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS_MBIR ; 
 unsigned int MBIR_RXMBF ; 
 unsigned int MBIR_RXMBFA ; 
 unsigned int MBIR_TXMBF ; 
 unsigned int MBIR_TXMBFA ; 
 int /*<<< orphan*/  ks_err (struct ks_net*,char*) ; 
 int /*<<< orphan*/  ks_info (struct ks_net*,char*) ; 
 unsigned int ks_rdreg16 (struct ks_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_warn (struct ks_net*,char*) ; 

__attribute__((used)) static int ks_read_selftest(struct ks_net *ks)
{
	unsigned both_done = MBIR_TXMBF | MBIR_RXMBF;
	int ret = 0;
	unsigned rd;

	rd = ks_rdreg16(ks, KS_MBIR);

	if ((rd & both_done) != both_done) {
		ks_warn(ks, "Memory selftest not finished\n");
		return 0;
	}

	if (rd & MBIR_TXMBFA) {
		ks_err(ks, "TX memory selftest fails\n");
		ret |= 1;
	}

	if (rd & MBIR_RXMBFA) {
		ks_err(ks, "RX memory selftest fails\n");
		ret |= 2;
	}

	ks_info(ks, "the selftest passes\n");
	return ret;
}