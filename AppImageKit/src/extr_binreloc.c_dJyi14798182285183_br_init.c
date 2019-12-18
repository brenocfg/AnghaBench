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
typedef  int /*<<< orphan*/  BrInitError ;

/* Variables and functions */
 int /*<<< orphan*/ * _br_find_exe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * exe ; 

int
br_init (BrInitError *error)
{
	exe = _br_find_exe (error);
	return exe != NULL;
}