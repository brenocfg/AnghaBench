#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* path; scalar_t__ bitcount; } ;
typedef  TYPE_1__ PathCounter ;

/* Variables and functions */
 int NUM_CODEBOOKS ; 
 int ZERO_PATH ; 

__attribute__((used)) static void clear_path_counter(PathCounter *path_counter)
{
    unsigned int i;

    for (i = 0; i < NUM_CODEBOOKS + 1; i++) {
        path_counter[i].path[0]  = ZERO_PATH;
        path_counter[i].path[1]  =      0x00;
        path_counter[i].bitcount =         0;
    }
}