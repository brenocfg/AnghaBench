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
struct gru_state {int gs_tgh_local_shift; } ;

/* Variables and functions */
 int uv_blade_processor_id () ; 

__attribute__((used)) static inline int get_on_blade_tgh(struct gru_state *gru)
{
	return uv_blade_processor_id() >> gru->gs_tgh_local_shift;
}