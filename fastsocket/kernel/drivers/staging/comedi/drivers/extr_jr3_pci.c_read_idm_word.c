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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 scalar_t__ isxdigit (int /*<<< orphan*/  const) ; 
 char tolower (int /*<<< orphan*/  const) ; 

int read_idm_word(const u8 * data, size_t size, int *pos, unsigned int *val)
{
	int result = 0;
	if (pos != 0 && val != 0) {
		/*  Skip over non hex */
		for (; *pos < size && !isxdigit(data[*pos]); (*pos)++) {
		}
		/*  Collect value */
		*val = 0;
		for (; *pos < size && isxdigit(data[*pos]); (*pos)++) {
			char ch = tolower(data[*pos]);
			result = 1;
			if ('0' <= ch && ch <= '9') {
				*val = (*val << 4) + (ch - '0');
			} else if ('a' <= ch && ch <= 'f') {
				*val = (*val << 4) + (ch - 'a' + 10);
			}
		}
	}
	return result;
}