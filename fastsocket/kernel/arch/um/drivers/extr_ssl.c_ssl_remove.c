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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int line_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  serial_lines ; 

__attribute__((used)) static int ssl_remove(int n, char **error_out)
{
	return line_remove(serial_lines, ARRAY_SIZE(serial_lines), n,
			   error_out);
}