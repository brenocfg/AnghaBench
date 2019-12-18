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
typedef  int /*<<< orphan*/  u8 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_MF_FCOE_AFEX (struct bnx2x*) ; 
 scalar_t__ IS_MF_STORAGE_SD (struct bnx2x*) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool bnx2x_is_valid_ether_addr(struct bnx2x *bp, u8 *addr)
{
	if (is_valid_ether_addr(addr) ||
	    (is_zero_ether_addr(addr) &&
	     (IS_MF_STORAGE_SD(bp) || IS_MF_FCOE_AFEX(bp))))
		return true;

	return false;
}