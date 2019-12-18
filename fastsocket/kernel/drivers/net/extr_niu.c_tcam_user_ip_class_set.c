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
struct niu {int dummy; } ;

/* Variables and functions */
 unsigned long CLASS_CODE_USER_PROG1 ; 
 unsigned long CLASS_CODE_USER_PROG4 ; 
 int EINVAL ; 
 unsigned long L3_CLS (unsigned long) ; 
 int L3_CLS_IPVER ; 
 int L3_CLS_PID ; 
 int L3_CLS_PID_SHIFT ; 
 int L3_CLS_TOS ; 
 int L3_CLS_TOSMASK ; 
 int L3_CLS_TOSMASK_SHIFT ; 
 int L3_CLS_TOS_SHIFT ; 
 int nr64 (unsigned long) ; 
 int /*<<< orphan*/  nw64 (unsigned long,int) ; 

__attribute__((used)) static int tcam_user_ip_class_set(struct niu *np, unsigned long class,
				  int ipv6, u64 protocol_id,
				  u64 tos_mask, u64 tos_val)
{
	unsigned long reg;
	u64 val;

	if (class < CLASS_CODE_USER_PROG1 ||
	    class > CLASS_CODE_USER_PROG4 ||
	    (protocol_id & ~(u64)0xff) != 0 ||
	    (tos_mask & ~(u64)0xff) != 0 ||
	    (tos_val & ~(u64)0xff) != 0)
		return -EINVAL;

	reg = L3_CLS(class - CLASS_CODE_USER_PROG1);
	val = nr64(reg);
	val &= ~(L3_CLS_IPVER | L3_CLS_PID |
		 L3_CLS_TOSMASK | L3_CLS_TOS);
	if (ipv6)
		val |= L3_CLS_IPVER;
	val |= (protocol_id << L3_CLS_PID_SHIFT);
	val |= (tos_mask << L3_CLS_TOSMASK_SHIFT);
	val |= (tos_val << L3_CLS_TOS_SHIFT);
	nw64(reg, val);

	return 0;
}