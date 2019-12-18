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
typedef  scalar_t__ uintmax_t ;
typedef  scalar_t__ strtol_error ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 scalar_t__ LONGINT_INVALID_SUFFIX_CHAR ; 
 scalar_t__ LONGINT_OK ; 
 scalar_t__ UINTMAX_MAX ; 
 scalar_t__* ignore_initial ; 
 int /*<<< orphan*/  try_help (char*,char const*) ; 
 int /*<<< orphan*/  valid_suffixes ; 
 scalar_t__ xstrtoumax (char const*,char**,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
specify_ignore_initial (int f, char **argptr, char delimiter)
{
  uintmax_t val;
  off_t o;
  char const *arg = *argptr;
  strtol_error e = xstrtoumax (arg, argptr, 0, &val, valid_suffixes);
  if (! (e == LONGINT_OK
	 || (e == LONGINT_INVALID_SUFFIX_CHAR && **argptr == delimiter))
      || (o = val) < 0 || o != val || val == UINTMAX_MAX)
    try_help ("invalid --ignore-initial value `%s'", arg);
  if (ignore_initial[f] < o)
    ignore_initial[f] = o;
}