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
struct tcf_walker {int dummy; } ;
struct tcf_proto {int dummy; } ;

/* Variables and functions */
 int __tcindex_delete (struct tcf_proto*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcindex_destroy_element(struct tcf_proto *tp,
    unsigned long arg, struct tcf_walker *walker)
{
	return __tcindex_delete(tp, arg, 0);
}