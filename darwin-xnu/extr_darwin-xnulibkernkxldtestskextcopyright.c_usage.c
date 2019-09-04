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
 char* gProgname ; 
 int /*<<< orphan*/  printFormat () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
usage(void)
{
    printf("usage: %s [path to kext]\n\n"
           "This program validates the copyright string in a kext's info "
           "dictionary.\n\n", gProgname);

    printFormat();
}