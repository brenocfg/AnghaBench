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
typedef  int uint8_t ;

/* Variables and functions */
 int CONTEXT_SIZE ; 

__attribute__((used)) static int contains_non_128(uint8_t (*initial_state)[CONTEXT_SIZE],
                            int nb_contexts)
{
    if (!initial_state)
        return 0;
    for (int i = 0; i < nb_contexts; i++)
        for (int j = 0; j < CONTEXT_SIZE; j++)
            if (initial_state[i][j] != 128)
                return 1;
    return 0;
}