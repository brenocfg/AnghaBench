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
 int ETIME ; 
 int ipw_read32 (struct ipw_priv*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int ipw_poll_bit(struct ipw_priv *priv, u32 addr, u32 mask,
			       int timeout)
{
	int i = 0;

	do {
		if ((ipw_read32(priv, addr) & mask) == mask)
			return i;
		mdelay(10);
		i += 10;
	} while (i < timeout);

	return -ETIME;
}