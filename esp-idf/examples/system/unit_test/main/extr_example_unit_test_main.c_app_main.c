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
typedef  int /*<<< orphan*/  numbers ;

/* Variables and functions */
 int* calloc (int const,int) ; 
 int const esp_random () ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int testable_mean (int*,int const) ; 

void app_main(void)
{
    const int count = 32;
    const int max = 100;

    printf("In main application. Collecting %d random numbers from 1 to %d:\n", count, max);
    int *numbers = calloc(count, sizeof(numbers[0]));
    for (int i = 0; i < count; ++i) {
        numbers[i] = 1 + esp_random() % (max - 1);
        printf("%4d ", numbers[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }

    int mean = testable_mean(numbers, count);
    printf("\nMean: %d\n", mean);
    free(numbers);
}