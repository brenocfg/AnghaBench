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
struct set_telem {int /*<<< orphan*/  timeout; } ;
struct list_set {int dummy; } ;

/* Variables and functions */
 int ip_set_timeout_test (int /*<<< orphan*/ ) ; 
 struct set_telem* list_set_telem (struct list_set const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
list_set_timeout(const struct list_set *map, u32 id)
{
	const struct set_telem *elem = list_set_telem(map, id);

	return ip_set_timeout_test(elem->timeout);
}