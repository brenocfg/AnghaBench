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
typedef  int u8 ;
struct ds1286_priv {int /*<<< orphan*/ * rtcregs; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u8 ds1286_rtc_read(struct ds1286_priv *priv, int reg)
{
	return __raw_readl(&priv->rtcregs[reg]) & 0xff;
}