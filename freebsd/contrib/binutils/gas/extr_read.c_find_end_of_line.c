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
 char* _find_end_of_line (char*,int,int /*<<< orphan*/ ) ; 

char *
find_end_of_line (char *s, int mri_string)
{
  return _find_end_of_line (s, mri_string, 0);
}