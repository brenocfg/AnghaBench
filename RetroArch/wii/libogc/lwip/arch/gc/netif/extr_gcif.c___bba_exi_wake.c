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
struct bba_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_CHANNEL_0 ; 
 int /*<<< orphan*/  EXI_Unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void __bba_exi_wake(struct bba_priv *priv)
{
	EXI_Unlock(EXI_CHANNEL_0);
}