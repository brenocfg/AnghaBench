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
struct work_stuff {int dummy; } ;
typedef  int /*<<< orphan*/  string ;

/* Variables and functions */
 scalar_t__ ISDIGIT (unsigned char) ; 
 int demangle_expression (struct work_stuff*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_appendn (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  tk_real ; 

__attribute__((used)) static int
demangle_real_value (struct work_stuff *work,
                     const char **mangled, string *s)
{
  if (**mangled == 'E')
    return demangle_expression (work, mangled, s, tk_real);

  if (**mangled == 'm')
    {
      string_appendn (s, "-", 1);
      (*mangled)++;
    }
  while (ISDIGIT ((unsigned char)**mangled))
    {
      string_appendn (s, *mangled, 1);
      (*mangled)++;
    }
  if (**mangled == '.') /* fraction */
    {
      string_appendn (s, ".", 1);
      (*mangled)++;
      while (ISDIGIT ((unsigned char)**mangled))
	{
	  string_appendn (s, *mangled, 1);
	  (*mangled)++;
	}
    }
  if (**mangled == 'e') /* exponent */
    {
      string_appendn (s, "e", 1);
      (*mangled)++;
      while (ISDIGIT ((unsigned char)**mangled))
	{
	  string_appendn (s, *mangled, 1);
	  (*mangled)++;
	}
    }

  return 1;
}