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
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
give_help (void)
{
  fprintf (stderr, "%s", _("\
ed:\tEdit then use both versions, each decorated with a header.\n\
eb:\tEdit then use both versions.\n\
el or e1:\tEdit then use the left version.\n\
er or e2:\tEdit then use the right version.\n\
e:\tDiscard both versions then edit a new one.\n\
l or 1:\tUse the left version.\n\
r or 2:\tUse the right version.\n\
s:\tSilently include common lines.\n\
v:\tVerbosely include common lines.\n\
q:\tQuit.\n\
"));
}