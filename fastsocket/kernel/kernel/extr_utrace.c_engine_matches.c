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
struct utrace_engine_ops {int dummy; } ;
struct utrace_engine {void* data; struct utrace_engine_ops const* ops; } ;

/* Variables and functions */
 int UTRACE_ATTACH_MATCH_DATA ; 
 int UTRACE_ATTACH_MATCH_OPS ; 
 struct utrace_engine_ops const utrace_detached_ops ; 

__attribute__((used)) static bool engine_matches(struct utrace_engine *engine, int flags,
			   const struct utrace_engine_ops *ops, void *data)
{
	if ((flags & UTRACE_ATTACH_MATCH_OPS) && engine->ops != ops)
		return false;
	if ((flags & UTRACE_ATTACH_MATCH_DATA) && engine->data != data)
		return false;
	return engine->ops && engine->ops != &utrace_detached_ops;
}