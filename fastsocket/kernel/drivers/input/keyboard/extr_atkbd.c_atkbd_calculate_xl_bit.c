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
struct atkbd {int /*<<< orphan*/  xl_bit; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned char*) ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ *) ; 
 unsigned char* xl_table ; 

__attribute__((used)) static void atkbd_calculate_xl_bit(struct atkbd *atkbd, unsigned char code)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(xl_table); i++) {
		if (!((code ^ xl_table[i]) & 0x7f)) {
			if (code & 0x80)
				__clear_bit(i, &atkbd->xl_bit);
			else
				__set_bit(i, &atkbd->xl_bit);
			break;
		}
	}
}