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
 int CHAR_SET_SIZE ; 
 scalar_t__ ISALNUM (int) ; 
 int /*<<< orphan*/  Sword ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * re_syntax_table ; 

__attribute__((used)) static void
init_syntax_once (void)
{
   register int c;
   static int done = 0;

   if (done)
     return;
   bzero (re_syntax_table, sizeof re_syntax_table);

   for (c = 0; c < CHAR_SET_SIZE; ++c)
     if (ISALNUM (c))
	re_syntax_table[c] = Sword;

   re_syntax_table['_'] = Sword;

   done = 1;
}