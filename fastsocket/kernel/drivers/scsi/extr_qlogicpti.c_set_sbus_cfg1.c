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
typedef  int u16 ;
struct qlogicpti {int bursts; scalar_t__ qregs; } ;

/* Variables and functions */
 int DMA_BURST16 ; 
 int DMA_BURST32 ; 
 int DMA_BURST64 ; 
 int DMA_BURST8 ; 
 scalar_t__ SBUS_CFG1 ; 
 int SBUS_CFG1_B16 ; 
 int SBUS_CFG1_B32 ; 
 int SBUS_CFG1_B64 ; 
 int SBUS_CFG1_B8 ; 
 int SBUS_CFG1_BENAB ; 
 scalar_t__ sbus_can_burst64 () ; 
 int /*<<< orphan*/  sbus_writew (int,scalar_t__) ; 

__attribute__((used)) static inline void set_sbus_cfg1(struct qlogicpti *qpti)
{
	u16 val;
	u8 bursts = qpti->bursts;

#if 0	/* It appears that at least PTI cards do not support
	 * 64-byte bursts and that setting the B64 bit actually
	 * is a nop and the chip ends up using the smallest burst
	 * size. -DaveM
	 */
	if (sbus_can_burst64() && (bursts & DMA_BURST64)) {
		val = (SBUS_CFG1_BENAB | SBUS_CFG1_B64);
	} else
#endif
	if (bursts & DMA_BURST32) {
		val = (SBUS_CFG1_BENAB | SBUS_CFG1_B32);
	} else if (bursts & DMA_BURST16) {
		val = (SBUS_CFG1_BENAB | SBUS_CFG1_B16);
	} else if (bursts & DMA_BURST8) {
		val = (SBUS_CFG1_BENAB | SBUS_CFG1_B8);
	} else {
		val = 0; /* No sbus bursts for you... */
	}
	sbus_writew(val, qpti->qregs + SBUS_CFG1);
}