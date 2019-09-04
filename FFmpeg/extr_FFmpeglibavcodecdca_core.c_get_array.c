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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  get_sbits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void get_array(GetBitContext *s, int32_t *array, int size, int n)
{
    int i;

    for (i = 0; i < size; i++)
        array[i] = get_sbits(s, n);
}