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
 int /*<<< orphan*/  PrintSpiralMatrix (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main(void)
{
    printf("-==- test for n=-1 -==-\n");
    PrintSpiralMatrix(-1);
    printf("\n");

    printf("-==- test for n=0 -==-\n");
    PrintSpiralMatrix(0);
    printf("\n");

    printf("-==- test for n=1 -==-\n");
    PrintSpiralMatrix(1);
    printf("\n");

    printf("-==- test for n=2 -==-\n");
    PrintSpiralMatrix(2);
    printf("\n");

    printf("-==- test for n=3 -==-\n");
    PrintSpiralMatrix(3);
    printf("\n");

    printf("-==- test for n=4 -==-\n");
    PrintSpiralMatrix(4);
    printf("\n");

    printf("-==- test for n=5 -==-\n");
    PrintSpiralMatrix(5);
    printf("\n");

    return 0;
}