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
struct ocfs2_alloc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_free_ac_resource (struct ocfs2_alloc_context*) ; 

void ocfs2_free_alloc_context(struct ocfs2_alloc_context *ac)
{
	ocfs2_free_ac_resource(ac);
	kfree(ac);
}