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

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  clac () ; 
 scalar_t__ pmap_smap_enabled ; 
 int /*<<< orphan*/  smaplog_add_entry (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void user_access_disable(void) {
	if (pmap_smap_enabled) {
		clac();
#if ENABLE_SMAPLOG
		smaplog_add_entry(FALSE);
#endif
	}
}