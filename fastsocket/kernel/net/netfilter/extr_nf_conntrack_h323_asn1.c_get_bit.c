#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* cur; int bit; } ;
typedef  TYPE_1__ bitstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  INC_BIT (TYPE_1__*) ; 

__attribute__((used)) static unsigned int get_bit(bitstr_t *bs)
{
	unsigned int b = (*bs->cur) & (0x80 >> bs->bit);

	INC_BIT(bs);

	return b;
}