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
 int /*<<< orphan*/  flag_m68k_mri ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/ * is_end_of_line ; 
 int /*<<< orphan*/  know (int /*<<< orphan*/ ) ; 

char *
mri_comment_field (char *stopcp)
{
  char *s;
#ifdef TC_M68K
  int inquote = 0;

  know (flag_m68k_mri);

  for (s = input_line_pointer;
       ((!is_end_of_line[(unsigned char) *s] && *s != ' ' && *s != '\t')
	|| inquote);
       s++)
    {
      if (*s == '\'')
	inquote = !inquote;
    }
#else
  for (s = input_line_pointer;
       !is_end_of_line[(unsigned char) *s];
       s++)
    ;
#endif
  *stopcp = *s;
  *s = '\0';

  return s;
}