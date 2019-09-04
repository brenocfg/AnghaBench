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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  R_TABLE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ff_amr_bit_reorder(uint16_t *out, int size,
                                      const uint8_t *data,
                                      const R_TABLE_TYPE *ord_table)
{
    int field_size;

    memset(out, 0, size);
    while ((field_size = *ord_table++)) {
        int field = 0;
        int field_offset = *ord_table++;
        while (field_size--) {
           int bit = *ord_table++;
           field <<= 1;
           field |= data[bit >> 3] >> (bit & 7) & 1;
        }
        out[field_offset >> 1] = field;
    }
}