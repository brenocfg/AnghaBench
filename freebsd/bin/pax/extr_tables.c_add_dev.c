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
struct TYPE_4__ {int /*<<< orphan*/  st_dev; } ;
struct TYPE_5__ {TYPE_1__ sb; } ;
typedef  TYPE_2__ ARCHD ;

/* Variables and functions */
 int /*<<< orphan*/ * chk_dev (int /*<<< orphan*/ ,int) ; 

int
add_dev(ARCHD *arcn)
{
	if (chk_dev(arcn->sb.st_dev, 1) == NULL)
		return(-1);
	return(0);
}