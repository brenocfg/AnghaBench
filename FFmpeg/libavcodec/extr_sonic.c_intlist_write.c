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
typedef  int /*<<< orphan*/  RangeCoder ;

/* Variables and functions */
 int /*<<< orphan*/  put_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int intlist_write(RangeCoder *c, uint8_t *state, int *buf, int entries, int base_2_part)
{
    int i;

    for (i = 0; i < entries; i++)
        put_symbol(c, state, buf[i], 1, NULL, NULL);

    return 1;
}