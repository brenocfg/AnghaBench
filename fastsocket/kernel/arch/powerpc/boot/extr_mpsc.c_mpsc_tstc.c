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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ MPSC_INTR_CAUSE ; 
 int MPSC_INTR_CAUSE_RCC ; 
 int in_le32 (int /*<<< orphan*/ *) ; 
 scalar_t__ mpscintr_base ; 

__attribute__((used)) static u8 mpsc_tstc(void)
{
	return (u8)((in_le32((u32 *)(mpscintr_base + MPSC_INTR_CAUSE))
				& MPSC_INTR_CAUSE_RCC) != 0);
}