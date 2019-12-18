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
typedef  int /*<<< orphan*/  u64 ;
struct ipz_eq_handle {int /*<<< orphan*/  handle; } ;
struct ipz_adapter_handle {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_RESET_EVENTS ; 
 int /*<<< orphan*/  ehca_plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 hipz_h_reset_event(const struct ipz_adapter_handle adapter_handle,
		       struct ipz_eq_handle eq_handle,
		       const u64 event_mask)
{
	return ehca_plpar_hcall_norets(H_RESET_EVENTS,
				       adapter_handle.handle, /* r4 */
				       eq_handle.handle,      /* r5 */
				       event_mask,	      /* r6 */
				       0, 0, 0, 0);
}