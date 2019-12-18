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
struct sidtab {int dummy; } ;
struct context {int dummy; } ;

/* Variables and functions */
 int sidtab_insert (struct sidtab*,int /*<<< orphan*/ ,struct context*) ; 

__attribute__((used)) static int clone_sid(u32 sid,
		     struct context *context,
		     void *arg)
{
	struct sidtab *s = arg;

	return sidtab_insert(s, sid, context);
}