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
 char* DCNGETTEXT (int /*<<< orphan*/ *,char const*,char const*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LC_MESSAGES ; 

char *
NGETTEXT (const char *msgid1, const char *msgid2, unsigned long int n)
{
  return DCNGETTEXT (NULL, msgid1, msgid2, n, LC_MESSAGES);
}