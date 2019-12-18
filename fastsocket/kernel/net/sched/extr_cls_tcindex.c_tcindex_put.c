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
struct tcf_proto {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,struct tcf_proto*,unsigned long) ; 

__attribute__((used)) static void tcindex_put(struct tcf_proto *tp, unsigned long f)
{
	pr_debug("tcindex_put(tp %p,f 0x%lx)\n", tp, f);
}