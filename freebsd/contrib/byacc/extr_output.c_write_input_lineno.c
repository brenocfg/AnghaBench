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
 int /*<<< orphan*/  code_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_file_name ; 
 int /*<<< orphan*/  lflag ; 
 char* line_format ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  outline ; 

__attribute__((used)) static void
write_input_lineno(void)
{
    if (!lflag)
    {
	++outline;
	fprintf(code_file, line_format, lineno, input_file_name);
    }
}