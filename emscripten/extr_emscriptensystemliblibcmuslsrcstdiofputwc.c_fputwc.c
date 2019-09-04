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
typedef  int /*<<< orphan*/  wint_t ;
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __fputwc_unlocked (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

wint_t fputwc(wchar_t c, FILE *f)
{
	FLOCK(f);
	c = __fputwc_unlocked(c, f);
	FUNLOCK(f);
	return c;
}