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
typedef  int u16 ;
struct ks_net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS_TXMIR ; 
 int ks_rdreg16 (struct ks_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 ks_tx_fifo_space(struct ks_net *ks)
{
	return ks_rdreg16(ks, KS_TXMIR) & 0x1fff;
}