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
 int /*<<< orphan*/  outline ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
putc_code(FILE * fp, int c)
{
    if ((c == '\n') && (fp == code_file))
	++outline;
    putc(c, fp);
}