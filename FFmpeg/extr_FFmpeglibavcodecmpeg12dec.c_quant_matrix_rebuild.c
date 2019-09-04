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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void quant_matrix_rebuild(uint16_t *matrix, const uint8_t *old_perm,
                                 const uint8_t *new_perm)
{
    uint16_t temp_matrix[64];
    int i;

    memcpy(temp_matrix, matrix, 64 * sizeof(uint16_t));

    for (i = 0; i < 64; i++)
        matrix[new_perm[i]] = temp_matrix[old_perm[i]];
}