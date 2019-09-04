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
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  munmap (char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  putchar (char) ; 

int main() {
    printf("*\n");
    FILE *f = fopen("data.dat", "r");
    char *m;
    m = (char*)mmap(NULL, 9000, PROT_READ, MAP_PRIVATE, fileno(f), 0);
    for (int i = 0; i < 20; i++) putchar(m[i]);
    munmap(m, 9000);
    printf("\n");
    m = (char*)mmap(NULL, 9000, PROT_READ, MAP_PRIVATE, fileno(f), 4096);
    for (int i = 0; i < 20; i++) putchar(m[i]);
    munmap(m, 9000);
    printf("\n*\n");

#ifdef REPORT_RESULT
    REPORT_RESULT(1);
#endif
    return 0;
}