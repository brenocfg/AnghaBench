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

/* Variables and functions */
 int GRU_SIZE ; 

__attribute__((used)) static inline void *gru_chiplet_vaddr(void *vaddr, int pnode, int chiplet)
{
	return vaddr + GRU_SIZE * (2 * pnode  + chiplet);
}