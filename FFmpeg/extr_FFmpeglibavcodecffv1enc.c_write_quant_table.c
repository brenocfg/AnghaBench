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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  state ;
typedef  scalar_t__ int16_t ;
typedef  int /*<<< orphan*/  RangeCoder ;

/* Variables and functions */
 int CONTEXT_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_quant_table(RangeCoder *c, int16_t *quant_table)
{
    int last = 0;
    int i;
    uint8_t state[CONTEXT_SIZE];
    memset(state, 128, sizeof(state));

    for (i = 1; i < 128; i++)
        if (quant_table[i] != quant_table[i - 1]) {
            put_symbol(c, state, i - last - 1, 0);
            last = i;
        }
    put_symbol(c, state, i - last - 1, 0);
}