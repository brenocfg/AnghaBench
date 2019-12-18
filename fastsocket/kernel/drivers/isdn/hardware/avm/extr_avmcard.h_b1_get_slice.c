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
 int /*<<< orphan*/  b1_get_byte (unsigned int) ; 
 unsigned int b1_get_word (unsigned int) ; 

__attribute__((used)) static inline unsigned int b1_get_slice(unsigned int base,
					unsigned char *dp)
{
	unsigned int len, i;

	len = i = b1_get_word(base);
	while (i-- > 0) *dp++ = b1_get_byte(base);
	return len;
}