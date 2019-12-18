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
struct binder_ref {int debug_id; int desc; int strong; int weak; TYPE_1__* node; int /*<<< orphan*/  death; } ;
struct TYPE_2__ {int debug_id; scalar_t__ proc; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,char*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *print_binder_ref(char *buf, char *end, struct binder_ref *ref)
{
	buf += snprintf(buf, end - buf,
			"  ref %d: desc %d %snode %d s %d w %d d %p\n",
			ref->debug_id, ref->desc,
			ref->node->proc ? "" : "dead ", ref->node->debug_id,
			ref->strong, ref->weak, ref->death);
	return buf;
}