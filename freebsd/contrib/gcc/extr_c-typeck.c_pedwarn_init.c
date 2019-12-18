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
 int /*<<< orphan*/  pedwarn (char*,char*) ; 
 char* print_spelling (char*) ; 
 scalar_t__ spelling_length () ; 

void
pedwarn_init (const char *msgid)
{
  char *ofwhat;

  pedwarn ("%s", _(msgid));
  ofwhat = print_spelling ((char *) alloca (spelling_length () + 1));
  if (*ofwhat)
    pedwarn ("(near initialization for %qs)", ofwhat);
}