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
typedef  int /*<<< orphan*/  optab ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_MODE_DECIMAL_FLOAT ; 
 int /*<<< orphan*/  MAX_MODE_FLOAT ; 
 int /*<<< orphan*/  MIN_MODE_DECIMAL_FLOAT ; 
 int /*<<< orphan*/  MIN_MODE_FLOAT ; 
 int /*<<< orphan*/  init_libfuncs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
init_floating_libfuncs (optab optable, const char *opname, int suffix)
{
  init_libfuncs (optable, MIN_MODE_FLOAT, MAX_MODE_FLOAT, opname, suffix);
  init_libfuncs (optable, MIN_MODE_DECIMAL_FLOAT, MAX_MODE_DECIMAL_FLOAT,
		 opname, suffix);
}