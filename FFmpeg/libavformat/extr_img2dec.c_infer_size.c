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
 int FF_ARRAY_ELEMS (int**) ; 
 int** sizes ; 

__attribute__((used)) static int infer_size(int *width_ptr, int *height_ptr, int size)
{
    int i;

    for (i = 0; i < FF_ARRAY_ELEMS(sizes); i++) {
        if ((sizes[i][0] * sizes[i][1]) == size) {
            *width_ptr  = sizes[i][0];
            *height_ptr = sizes[i][1];
            return 0;
        }
    }

    return -1;
}