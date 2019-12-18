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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  printfail () ; 

void fexpect(char *file, int line, int a, int b) {
    if (a == b)
        return;
    printfail();
    printf("%s:%d: %d expected, but got %d\n", file, line, a, b);
    exit(1);
}