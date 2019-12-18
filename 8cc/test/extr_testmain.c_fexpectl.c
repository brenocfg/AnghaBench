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
 int /*<<< orphan*/  printf (char*,char*,int,long,long) ; 
 int /*<<< orphan*/  printfail () ; 

void fexpectl(char *file, int line, long a, long b) {
    if (a == b)
        return;
    printfail();
    printf("%s:%d: %ld expected, but got %ld\n", file, line, a, b);
    exit(1);
}