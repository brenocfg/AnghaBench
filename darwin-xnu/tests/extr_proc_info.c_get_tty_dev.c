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
typedef  int /*<<< orphan*/  uint32_t ;
struct stat {scalar_t__ st_rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  ttyname (int) ; 

uint32_t
get_tty_dev()
{
	struct stat buf;
	stat(ttyname(1), &buf);
	return ((uint32_t)buf.st_rdev);
}