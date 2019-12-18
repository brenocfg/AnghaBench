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
typedef  int /*<<< orphan*/  u64 ;
struct niu {int dummy; } ;

/* Variables and functions */
 unsigned long CLASS_CODE_ETHERTYPE1 ; 
 unsigned long CLASS_CODE_ETHERTYPE2 ; 
 int EINVAL ; 
 unsigned long L2_CLS (unsigned long) ; 
 int /*<<< orphan*/  L2_CLS_VLD ; 
 int /*<<< orphan*/  nr64 (unsigned long) ; 
 int /*<<< orphan*/  nw64 (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcam_user_eth_class_enable(struct niu *np, unsigned long class,
				      int on)
{
	unsigned long reg;
	u64 val;

	if (class < CLASS_CODE_ETHERTYPE1 ||
	    class > CLASS_CODE_ETHERTYPE2)
		return -EINVAL;

	reg = L2_CLS(class - CLASS_CODE_ETHERTYPE1);
	val = nr64(reg);
	if (on)
		val |= L2_CLS_VLD;
	else
		val &= ~L2_CLS_VLD;
	nw64(reg, val);

	return 0;
}