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
 int /*<<< orphan*/  disc_strings ; 
 int /*<<< orphan*/  disc_strings_length ; 
 int /*<<< orphan*/  left_exclusion (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ left_parens_or_brackets (char*) ; 

__attribute__((used)) static bool left_parens_or_brackets_excluding_disc(char *left)
{
   return left_parens_or_brackets(left)
      && !left_exclusion(left, disc_strings, disc_strings_length);
}