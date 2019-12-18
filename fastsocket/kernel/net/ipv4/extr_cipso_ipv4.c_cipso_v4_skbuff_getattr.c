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
struct sk_buff {int dummy; } ;
struct netlbl_lsm_secattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIPSO_V4_OPTPTR (struct sk_buff const*) ; 
 int cipso_v4_getattr (int /*<<< orphan*/ ,struct netlbl_lsm_secattr*) ; 

int cipso_v4_skbuff_getattr(const struct sk_buff *skb,
			    struct netlbl_lsm_secattr *secattr)
{
	return cipso_v4_getattr(CIPSO_V4_OPTPTR(skb), secattr);
}