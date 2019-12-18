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
typedef  int uint32_t ;

/* Variables and functions */
 int* malloc (int) ; 
 int* table_base ; 

__attribute__((used)) static uint32_t *
buzhash_init_table(uint32_t seed)
{
    int i;
    uint32_t *table = malloc(1024);
    for(i = 0; i < 256; i++)
    {
        table[i] = table_base[i] ^ seed;
    }
    return table;
}