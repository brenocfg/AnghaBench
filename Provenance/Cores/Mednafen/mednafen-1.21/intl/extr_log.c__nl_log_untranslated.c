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
 int /*<<< orphan*/  __libc_lock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __libc_lock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nl_log_untranslated_locked (char const*,char const*,char const*,char const*,int) ; 
 int /*<<< orphan*/  lock ; 

void
_nl_log_untranslated (const char *logfilename, const char *domainname,
                      const char *msgid1, const char *msgid2, int plural)
{
  __libc_lock_lock (lock);
  _nl_log_untranslated_locked (logfilename, domainname, msgid1, msgid2, plural);
  __libc_lock_unlock (lock);
}