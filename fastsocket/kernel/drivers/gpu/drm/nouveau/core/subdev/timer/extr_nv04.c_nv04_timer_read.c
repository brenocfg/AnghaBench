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
typedef  scalar_t__ u32 ;
struct nv04_timer_priv {int dummy; } ;
struct nouveau_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PTIMER_TIME_0 ; 
 int /*<<< orphan*/  NV04_PTIMER_TIME_1 ; 
 scalar_t__ nv_rd32 (struct nv04_timer_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64
nv04_timer_read(struct nouveau_timer *ptimer)
{
	struct nv04_timer_priv *priv = (void *)ptimer;
	u32 hi, lo;

	do {
		hi = nv_rd32(priv, NV04_PTIMER_TIME_1);
		lo = nv_rd32(priv, NV04_PTIMER_TIME_0);
	} while (hi != nv_rd32(priv, NV04_PTIMER_TIME_1));

	return ((u64)hi << 32 | lo);
}