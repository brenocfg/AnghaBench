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
 int EXIT_SUCCESS ; 
 char* PACKAGE_VERSION ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int
main(void)
{
    printf("%s\n", PACKAGE_VERSION);
    return EXIT_SUCCESS;
}