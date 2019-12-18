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
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int files_cnt ; 
 int get_num (char*) ; 

__attribute__((used)) static void
f_files(char *arg)
{

	files_cnt = get_num(arg);
	if (files_cnt < 1)
		errx(1, "files must be between 1 and %zu", SIZE_MAX);
}