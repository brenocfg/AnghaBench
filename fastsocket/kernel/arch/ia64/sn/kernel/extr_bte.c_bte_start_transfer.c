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
struct bteinfo_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTE_CTRL_STORE (struct bteinfo_s*,int) ; 
 int /*<<< orphan*/  BTE_LNSTAT_STORE (struct bteinfo_s*,int) ; 
 int IBLS_BUSY ; 
 scalar_t__ is_shub2 () ; 

__attribute__((used)) static inline void bte_start_transfer(struct bteinfo_s *bte, u64 len, u64 mode)
{
	if (is_shub2()) {
		BTE_CTRL_STORE(bte, (IBLS_BUSY | ((len) | (mode) << 24)));
	} else {
		BTE_LNSTAT_STORE(bte, len);
		BTE_CTRL_STORE(bte, mode);
	}
}