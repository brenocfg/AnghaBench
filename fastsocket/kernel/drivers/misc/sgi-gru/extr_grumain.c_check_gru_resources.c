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
struct gru_state {int gs_active_contexts; int /*<<< orphan*/  gs_dsr_map; int /*<<< orphan*/  gs_cbr_map; } ;

/* Variables and functions */
 int hweight64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_gru_resources(struct gru_state *gru, int cbr_au_count,
			       int dsr_au_count, int max_active_contexts)
{
	return hweight64(gru->gs_cbr_map) >= cbr_au_count
		&& hweight64(gru->gs_dsr_map) >= dsr_au_count
		&& gru->gs_active_contexts < max_active_contexts;
}