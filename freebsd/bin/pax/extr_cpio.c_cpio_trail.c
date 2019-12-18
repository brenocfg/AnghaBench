#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ st_size; } ;
struct TYPE_5__ {TYPE_1__ sb; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ ARCHD ;

/* Variables and functions */
 int /*<<< orphan*/  TRAILER ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cpio_trail(ARCHD *arcn)
{
	/*
	 * look for trailer id in file we are about to process
	 */
	if ((strcmp(arcn->name, TRAILER) == 0) && (arcn->sb.st_size == 0))
		return(0);
	return(-1);
}