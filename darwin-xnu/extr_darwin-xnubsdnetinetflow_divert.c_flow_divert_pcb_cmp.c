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
struct flow_divert_pcb {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int
flow_divert_pcb_cmp(const struct flow_divert_pcb *pcb_a, const struct flow_divert_pcb *pcb_b)
{
	return memcmp(&pcb_a->hash, &pcb_b->hash, sizeof(pcb_a->hash));
}