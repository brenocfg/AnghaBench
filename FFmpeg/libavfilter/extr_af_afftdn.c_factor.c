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

__attribute__((used)) static void factor(double *array, int size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            double d = array[j + i * size] / array[i + i * size];

            array[j + i * size] = d;
            for (int k = i + 1; k < size; k++) {
                array[j + k * size] -= d * array[i + k * size];
            }
        }
    }
}