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
typedef  size_t u_int32_t ;
typedef  int /*<<< orphan*/  array ;

/* Variables and functions */
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,char,...) ; 

__attribute__((used)) static int try_number(const char *data, size_t dlen, u_int32_t array[],
		      int array_size, char sep, char term)
{
	u_int32_t i, len;

	memset(array, 0, sizeof(array[0])*array_size);

	/* Keep data pointing at next char. */
	for (i = 0, len = 0; len < dlen && i < array_size; len++, data++) {
		if (*data >= '0' && *data <= '9') {
			array[i] = array[i]*10 + *data - '0';
		}
		else if (*data == sep)
			i++;
		else {
			/* Unexpected character; true if it's the
			   terminator and we're finished. */
			if (*data == term && i == array_size - 1)
				return len;

			pr_debug("Char %u (got %u nums) `%u' unexpected\n",
				 len, i, *data);
			return 0;
		}
	}
	pr_debug("Failed to fill %u numbers separated by %c\n",
		 array_size, sep);
	return 0;
}