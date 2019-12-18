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
struct utrace_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UTRACE_DETACH ; 

__attribute__((used)) static u32 utrace_detached_quiesce(u32 action, struct utrace_engine *engine,
				   unsigned long event)
{
	return UTRACE_DETACH;
}