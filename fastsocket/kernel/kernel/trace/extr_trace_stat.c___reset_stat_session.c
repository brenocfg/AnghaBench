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
struct TYPE_2__ {struct rb_node* rb_node; } ;
struct stat_session {TYPE_1__ stat_root; int /*<<< orphan*/  ts; } ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 TYPE_1__ RB_ROOT ; 
 struct rb_node* release_next (int /*<<< orphan*/ ,struct rb_node*) ; 

__attribute__((used)) static void __reset_stat_session(struct stat_session *session)
{
	struct rb_node *node = session->stat_root.rb_node;

	while (node)
		node = release_next(session->ts, node);

	session->stat_root = RB_ROOT;
}