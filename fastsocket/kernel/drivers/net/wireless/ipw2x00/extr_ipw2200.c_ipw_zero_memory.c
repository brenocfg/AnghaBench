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
typedef  int u32 ;
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_AUTOINC_ADDR ; 
 int /*<<< orphan*/  IPW_AUTOINC_DATA ; 
 int /*<<< orphan*/  _ipw_write32 (struct ipw_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ipw_zero_memory(struct ipw_priv *priv, u32 start, u32 count)
{
	count >>= 2;
	if (!count)
		return;
	_ipw_write32(priv, IPW_AUTOINC_ADDR, start);
	while (count--)
		_ipw_write32(priv, IPW_AUTOINC_DATA, 0);
}