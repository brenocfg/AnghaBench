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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int find_first_bit (unsigned long const*,int) ; 
 int find_next_bit (unsigned long const*,int,int) ; 
 int /*<<< orphan*/  test_bit (int,unsigned long const*) ; 

__attribute__((used)) static int bitmap_pos_to_ord(const unsigned long *buf, int pos, int bits)
{
	int i, ord;

	if (pos < 0 || pos >= bits || !test_bit(pos, buf))
		return -1;

	i = find_first_bit(buf, bits);
	ord = 0;
	while (i < pos) {
		i = find_next_bit(buf, bits, i + 1);
	     	ord++;
	}
	BUG_ON(i != pos);

	return ord;
}