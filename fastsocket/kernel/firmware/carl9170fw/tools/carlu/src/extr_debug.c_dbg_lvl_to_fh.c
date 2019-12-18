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
typedef  enum debug_level_t { ____Placeholder_debug_level_t } debug_level_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  ERROR 131 
#define  INFO 130 
#define  VERBOSE 129 
#define  WARNING 128 
 int /*<<< orphan*/ * _stddbg ; 
 int /*<<< orphan*/ * _stderr ; 
 int /*<<< orphan*/ * _stdout ; 

FILE *dbg_lvl_to_fh(const enum debug_level_t lvl)
{
	switch (lvl) {
	case ERROR:
	case WARNING:
		return _stderr;
	case INFO:
		return _stdout;
	case VERBOSE:
		return _stddbg;
	default:
		BUG_ON(1);
	}
}