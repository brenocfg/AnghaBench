#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ magic; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 scalar_t__ MGSLPC_MAGIC ; 
 int /*<<< orphan*/  printk (char const*,char*,char const*) ; 

__attribute__((used)) static inline bool mgslpc_paranoia_check(MGSLPC_INFO *info,
					char *name, const char *routine)
{
#ifdef MGSLPC_PARANOIA_CHECK
	static const char *badmagic =
		"Warning: bad magic number for mgsl struct (%s) in %s\n";
	static const char *badinfo =
		"Warning: null mgslpc_info for (%s) in %s\n";

	if (!info) {
		printk(badinfo, name, routine);
		return true;
	}
	if (info->magic != MGSLPC_MAGIC) {
		printk(badmagic, name, routine);
		return true;
	}
#else
	if (!info)
		return true;
#endif
	return false;
}