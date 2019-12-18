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
 int rand () ; 

__attribute__((used)) static int get_b_rand(void)
{
    static int ph = 32;         /* More bits than we will ever use */
    static int randseq;
    if (ph > 31) {              /* Num bits in return of rand() */
        ph = 0;
        randseq = rand();
    }
    return randseq & (1 << ph++);
}