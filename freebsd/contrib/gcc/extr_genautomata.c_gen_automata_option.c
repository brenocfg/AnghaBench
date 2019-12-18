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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ NDFA_OPTION ; 
 scalar_t__ NO_MINIMIZATION_OPTION ; 
 scalar_t__ PROGRESS_OPTION ; 
 scalar_t__ TIME_OPTION ; 
 scalar_t__ V_OPTION ; 
 scalar_t__ W_OPTION ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int ndfa_flag ; 
 int no_minimization_flag ; 
 int progress_flag ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,scalar_t__) ; 
 int time_flag ; 
 int v_flag ; 
 int w_flag ; 

__attribute__((used)) static void
gen_automata_option (rtx def)
{
  if (strcmp (XSTR (def, 0), NO_MINIMIZATION_OPTION + 1) == 0)
    no_minimization_flag = 1;
  else if (strcmp (XSTR (def, 0), TIME_OPTION + 1) == 0)
    time_flag = 1;
  else if (strcmp (XSTR (def, 0), V_OPTION + 1) == 0)
    v_flag = 1;
  else if (strcmp (XSTR (def, 0), W_OPTION + 1) == 0)
    w_flag = 1;
  else if (strcmp (XSTR (def, 0), NDFA_OPTION + 1) == 0)
    ndfa_flag = 1;
  else if (strcmp (XSTR (def, 0), PROGRESS_OPTION + 1) == 0)
    progress_flag = 1;
  else
    fatal ("invalid option `%s' in automata_option", XSTR (def, 0));
}