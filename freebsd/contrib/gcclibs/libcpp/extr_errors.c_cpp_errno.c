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
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  cpp_error (int /*<<< orphan*/ *,int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  xstrerror (int /*<<< orphan*/ ) ; 

void
cpp_errno (cpp_reader *pfile, int level, const char *msgid)
{
  if (msgid[0] == '\0')
    msgid = _("stdout");

  cpp_error (pfile, level, "%s: %s", msgid, xstrerror (errno));
}