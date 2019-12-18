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
 size_t fprintf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static size_t trace__fprintf_threads_header(FILE *fp)
{
	size_t printed;

	printed  = fprintf(fp, "\n _____________________________________________________________________\n");
	printed += fprintf(fp," __)    Summary of events    (__\n\n");
	printed += fprintf(fp,"              [ task - pid ]     [ events ] [ ratio ]  [ runtime ]\n");
	printed += fprintf(fp," _____________________________________________________________________\n\n");

	return printed;
}