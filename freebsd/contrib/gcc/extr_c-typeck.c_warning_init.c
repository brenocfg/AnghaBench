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
 char* _ (char const*) ; 
 scalar_t__ alloca (scalar_t__) ; 
 char* print_spelling (char*) ; 
 scalar_t__ spelling_length () ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
warning_init (const char *msgid)
{
  char *ofwhat;

  warning (0, "%s", _(msgid));
  ofwhat = print_spelling ((char *) alloca (spelling_length () + 1));
  if (*ofwhat)
    warning (0, "(near initialization for %qs)", ofwhat);
}