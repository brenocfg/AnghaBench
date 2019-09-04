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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __ftello_unlocked (int /*<<< orphan*/ *) ; 

off_t __ftello(FILE *f)
{
	off_t pos;
	FLOCK(f);
	pos = __ftello_unlocked(f);
	FUNLOCK(f);
	return pos;
}