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
struct TYPE_3__ {int val1; int val2; int next; } ;
typedef  TYPE_1__ OpcodeTable ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int ff_clz (int) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int*,int) ; 

__attribute__((used)) static int fill_optable(unsigned *table0, OpcodeTable *table1, int nb_elements)
{
    unsigned table2[256] = { 0 };
    unsigned x = 0;
    int val0, val1, i, j = 2, k = 0;

    table2[0] = table0[0];
    for (i = 0; i < nb_elements - 1; i++, table2[i] = val0) {
        val0 = table0[i + 1] + table2[i];
    }

    if (!table2[0]) {
        do {
            k++;
        } while (!table2[k]);
    }

    j = 2;
    for (i = 1024; i > 0; i--) {
        for (table1[x].val1 = k; k < 256 && j > table2[k]; k++);
        x = (x - 383) & 0x3FF;
        j++;
    }

    if (nb_elements > 0)
        memcpy(&table2[0], table0, 4 * nb_elements);

    for (i = 0; i < 1024; i++) {
        val0 = table1[i].val1;
        val1 = table2[val0];
        table2[val0]++;
        x = 31 - ff_clz(val1);
        if (x > 10)
            return AVERROR_INVALIDDATA;
        table1[i].val2 = 10 - x;
        table1[i].next = (val1 << table1[i].val2) - 1024;
    }

    return 0;
}