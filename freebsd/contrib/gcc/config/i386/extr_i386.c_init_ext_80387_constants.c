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
 int /*<<< orphan*/  XFmode ; 
 int ext_80387_constants_init ; 
 int /*<<< orphan*/ * ext_80387_constants_table ; 
 int /*<<< orphan*/  real_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  real_from_string (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
init_ext_80387_constants (void)
{
  static const char * cst[5] =
  {
    "0.3010299956639811952256464283594894482",  /* 0: fldlg2  */
    "0.6931471805599453094286904741849753009",  /* 1: fldln2  */
    "1.4426950408889634073876517827983434472",  /* 2: fldl2e  */
    "3.3219280948873623478083405569094566090",  /* 3: fldl2t  */
    "3.1415926535897932385128089594061862044",  /* 4: fldpi   */
  };
  int i;

  for (i = 0; i < 5; i++)
    {
      real_from_string (&ext_80387_constants_table[i], cst[i]);
      /* Ensure each constant is rounded to XFmode precision.  */
      real_convert (&ext_80387_constants_table[i],
		    XFmode, &ext_80387_constants_table[i]);
    }

  ext_80387_constants_init = 1;
}