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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(const char *program_name)
{
    fprintf(stderr, "usage: %s OPERATION entry1 [entry2]\n"
            "API example program to show how to manipulate resources "
            "accessed through AVIOContext.\n"
            "OPERATIONS:\n"
            "list      list content of the directory\n"
            "move      rename content in directory\n"
            "del       delete content in directory\n",
            program_name);
}