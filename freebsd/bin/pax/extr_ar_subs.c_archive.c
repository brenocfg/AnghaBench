#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ (* options ) () ;} ;
typedef  int /*<<< orphan*/  ARCHD ;

/* Variables and functions */
 TYPE_1__* frmt ; 
 scalar_t__ ftime_start () ; 
 scalar_t__ stub1 () ; 
 scalar_t__ uflag ; 
 int /*<<< orphan*/  wr_archive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ wr_start () ; 

void
archive(void)
{
	ARCHD archd;

	/*
	 * if we only are adding members that are newer, we need to save the
	 * mod times for all files; set up for writing; pass the format any
	 * options write the archive
	 */
	if ((uflag && (ftime_start() < 0)) || (wr_start() < 0))
		return;
	if ((*frmt->options)() < 0)
		return;

	wr_archive(&archd, 0);
}