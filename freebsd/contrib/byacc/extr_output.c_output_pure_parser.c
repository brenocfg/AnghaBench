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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  outline ; 
 int pure_parser ; 
 int /*<<< orphan*/  putc_code (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void
output_pure_parser(FILE * fp)
{
    putc_code(fp, '\n');

    if (fp == code_file)
	++outline;
    fprintf(fp, "#define YYPURE %d\n", pure_parser);
    putc_code(fp, '\n');
}