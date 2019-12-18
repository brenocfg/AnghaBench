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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  KMEMTRACE_TYPE_KMALLOC ; 
 int /*<<< orphan*/  kmemtrace_alloc (int /*<<< orphan*/ ,unsigned long,void const*,size_t,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kmemtrace_kmalloc_node(unsigned long call_site,
				   const void *ptr,
				   size_t bytes_req,
				   size_t bytes_alloc,
				   gfp_t gfp_flags,
				   int node)
{
	kmemtrace_alloc(KMEMTRACE_TYPE_KMALLOC, call_site, ptr,
			bytes_req, bytes_alloc, gfp_flags, node);
}