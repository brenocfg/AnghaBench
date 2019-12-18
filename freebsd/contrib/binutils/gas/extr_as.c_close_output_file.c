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
 int /*<<< orphan*/  out_file_name ; 
 int /*<<< orphan*/  output_file_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
close_output_file (void)
{
  output_file_close (out_file_name);
}