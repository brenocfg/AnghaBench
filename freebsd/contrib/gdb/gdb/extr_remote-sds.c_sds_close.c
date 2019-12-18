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
 int /*<<< orphan*/ * sds_desc ; 
 int /*<<< orphan*/  serial_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sds_close (int quitting)
{
  if (sds_desc)
    serial_close (sds_desc);
  sds_desc = NULL;
}