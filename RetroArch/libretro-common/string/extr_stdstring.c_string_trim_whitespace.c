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
 int /*<<< orphan*/  string_trim_whitespace_left (char* const) ; 
 int /*<<< orphan*/  string_trim_whitespace_right (char* const) ; 

char *string_trim_whitespace(char *const s)
{
   string_trim_whitespace_right(s);  /* order matters */
   string_trim_whitespace_left(s);

   return s;
}