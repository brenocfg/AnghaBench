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
typedef  scalar_t__ Lmid_t ;

/* Variables and functions */
 scalar_t__ LM_ID_BASE ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,scalar_t__,char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static void
dt_pid_objname(char *buf, size_t len, Lmid_t lmid, const char *obj)
{
#ifdef illumos
	if (lmid == LM_ID_BASE)
		(void) strncpy(buf, obj, len);
	else
		(void) snprintf(buf, len, "LM%lx`%s", lmid, obj);
#else
	(void) strncpy(buf, obj, len);
#endif
}