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
struct re_registers {int dummy; } ;
struct re_pattern_buffer {int dummy; } ;

/* Variables and functions */
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  alloca (int /*<<< orphan*/ ) ; 
 int byte_re_match_2_internal (struct re_pattern_buffer*,char const*,int,char const*,int,int,struct re_registers*,int) ; 
 int wcs_re_match_2_internal (struct re_pattern_buffer*,char const*,int,char const*,int,int,struct re_registers*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
re_match_2 (struct re_pattern_buffer *bufp, const char *string1, int size1,
            const char *string2, int size2, int pos,
            struct re_registers *regs, int stop)
{
  int result;
# ifdef MBS_SUPPORT
  if (MB_CUR_MAX != 1)
    result = wcs_re_match_2_internal (bufp, string1, size1, string2, size2,
				      pos, regs, stop,
				      NULL, 0, NULL, 0, NULL, NULL);
  else
# endif
    result = byte_re_match_2_internal (bufp, string1, size1, string2, size2,
				  pos, regs, stop);

#ifndef REGEX_MALLOC
# ifdef C_ALLOCA
  alloca (0);
# endif
#endif
  return result;
}