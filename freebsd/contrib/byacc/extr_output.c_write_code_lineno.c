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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * code_file ; 
 int /*<<< orphan*/  code_file_name ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lflag ; 
 char* line_format ; 
 scalar_t__ outline ; 

__attribute__((used)) static void
write_code_lineno(FILE * fp)
{
    if (!lflag && (fp == code_file))
    {
	++outline;
	fprintf(fp, line_format, outline + 1, code_file_name);
    }
}