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
struct cas_rx_comp {int /*<<< orphan*/  word4; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_COMP4_ZERO ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cas_rx_comp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void cas_rxc_init(struct cas_rx_comp *rxc)
{
	memset(rxc, 0, sizeof(*rxc));
	rxc->word4 = cpu_to_le64(RX_COMP4_ZERO);
}