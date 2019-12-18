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
struct il_priv {int dummy; } ;

/* Variables and functions */
 int _il_rd (struct il_priv*,int) ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int,int) ; 

__attribute__((used)) static inline void
_il_clear_bit(struct il_priv *il, u32 reg, u32 mask)
{
	_il_wr(il, reg, _il_rd(il, reg) & ~mask);
}