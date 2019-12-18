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
typedef  int /*<<< orphan*/  CREC ;

/* Variables and functions */
 long rand_long (long) ; 

void shuffle(CREC *array, long n) {
    long i, j;
    CREC tmp;
    for (i = n - 1; i > 0; i--) {
        j = rand_long(i + 1);
        tmp = array[j];
        array[j] = array[i];
        array[i] = tmp;
    }
}