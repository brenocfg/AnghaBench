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
struct itcw {int /*<<< orphan*/  num_tidaws; int /*<<< orphan*/  tcw; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcw_finalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void itcw_finalize(struct itcw *itcw)
{
	tcw_finalize(itcw->tcw, itcw->num_tidaws);
}