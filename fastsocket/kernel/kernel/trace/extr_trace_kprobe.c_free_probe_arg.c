#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  fn; } ;
struct probe_arg {int /*<<< orphan*/  comm; int /*<<< orphan*/  name; TYPE_1__ fetch; } ;

/* Variables and functions */
 scalar_t__ CHECK_FETCH_FUNCS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitfield ; 
 int /*<<< orphan*/  deref ; 
 int /*<<< orphan*/  free_bitfield_fetch_param (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_deref_fetch_param (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_symbol_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol ; 

__attribute__((used)) static void free_probe_arg(struct probe_arg *arg)
{
	if (CHECK_FETCH_FUNCS(bitfield, arg->fetch.fn))
		free_bitfield_fetch_param(arg->fetch.data);
	else if (CHECK_FETCH_FUNCS(deref, arg->fetch.fn))
		free_deref_fetch_param(arg->fetch.data);
	else if (CHECK_FETCH_FUNCS(symbol, arg->fetch.fn))
		free_symbol_cache(arg->fetch.data);
	kfree(arg->name);
	kfree(arg->comm);
}