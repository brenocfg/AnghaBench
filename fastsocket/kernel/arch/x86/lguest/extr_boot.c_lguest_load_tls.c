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
struct thread_struct {int /*<<< orphan*/  tls_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  LHCALL_LOAD_TLS ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lazy_hcall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  lazy_load_gs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lguest_load_tls(struct thread_struct *t, unsigned int cpu)
{
	/*
	 * There's one problem which normal hardware doesn't have: the Host
	 * can't handle us removing entries we're currently using.  So we clear
	 * the GS register here: if it's needed it'll be reloaded anyway.
	 */
	lazy_load_gs(0);
	lazy_hcall2(LHCALL_LOAD_TLS, __pa(&t->tls_array), cpu);
}