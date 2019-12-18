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
typedef  int /*<<< orphan*/  mode_t ;
typedef  scalar_t__ fio_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  remote_fileio_mode_to_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_fileio_to_be (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
remote_fileio_to_fio_mode (mode_t num, fio_mode_t fnum)
{
  remote_fileio_to_be (remote_fileio_mode_to_target(num), (char *) fnum, 4);
}