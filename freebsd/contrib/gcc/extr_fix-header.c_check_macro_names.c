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
typedef  scalar_t__* namelist ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 scalar_t__ cpp_defined (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  recognized_macro (scalar_t__*) ; 
 size_t strlen (scalar_t__*) ; 

__attribute__((used)) static void
check_macro_names (cpp_reader *pfile, namelist names)
{
  size_t len;
  while (*names)
    {
      len = strlen (names);
      if (cpp_defined (pfile, (const unsigned char *)names, len))
	recognized_macro (names);
      names += len + 1;
    }
}