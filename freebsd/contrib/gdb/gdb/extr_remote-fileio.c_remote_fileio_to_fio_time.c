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
typedef  scalar_t__ time_t ;
typedef  scalar_t__ fio_time_t ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  remote_fileio_to_be (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
remote_fileio_to_fio_time (time_t num, fio_time_t fnum)
{
  remote_fileio_to_be ((LONGEST) num, (char *) fnum, 4);
}