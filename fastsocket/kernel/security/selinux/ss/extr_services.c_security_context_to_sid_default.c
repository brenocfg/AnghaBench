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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int security_context_to_sid_core (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int security_context_to_sid_default(const char *scontext, u32 scontext_len,
				    u32 *sid, u32 def_sid, gfp_t gfp_flags)
{
	return security_context_to_sid_core(scontext, scontext_len,
					    sid, def_sid, gfp_flags, 1);
}