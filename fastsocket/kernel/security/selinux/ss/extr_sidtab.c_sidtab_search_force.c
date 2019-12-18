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
 struct context* sidtab_search_core (struct sidtab*,int /*<<< orphan*/ ,int) ; 

struct context *sidtab_search_force(struct sidtab *s, u32 sid)
{
	return sidtab_search_core(s, sid, 1);
}