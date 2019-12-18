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
typedef  int /*<<< orphan*/  u32 ;
struct bba_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_CHANNEL_0 ; 
 int /*<<< orphan*/  EXI_DEVICE_2 ; 
 scalar_t__ EXI_Lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int,char*) ; 
 int /*<<< orphan*/  LWP_ThreadSleep (int /*<<< orphan*/ ) ; 
 int NETIF_DEBUG ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __bba_exi_unlockcb ; 
 int /*<<< orphan*/  wait_exi_queue ; 

__attribute__((used)) static __inline__ void __bba_exi_stop(struct bba_priv *priv)
{
	u32 level;

	_CPU_ISR_Disable(level);
	while(EXI_Lock(EXI_CHANNEL_0,EXI_DEVICE_2,__bba_exi_unlockcb)==0) {
		LWIP_DEBUGF(NETIF_DEBUG|1,("__bba_exi_wait(exi locked)\n"));
		LWP_ThreadSleep(wait_exi_queue);
	}
	_CPU_ISR_Restore(level);
}