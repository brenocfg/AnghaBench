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
typedef  size_t u8 ;
struct xt_target {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct xt_target*) ; 
 struct xt_target* try_then_request_module (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xt_find_target (size_t,char const*,size_t) ; 
 int /*<<< orphan*/ * xt_prefix ; 

struct xt_target *xt_request_find_target(u8 af, const char *name, u8 revision)
{
	struct xt_target *target;

	target = try_then_request_module(xt_find_target(af, name, revision),
					 "%st_%s", xt_prefix[af], name);
	if (IS_ERR(target) || !target)
		return NULL;
	return target;
}