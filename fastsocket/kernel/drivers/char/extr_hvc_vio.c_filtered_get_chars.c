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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int EAGAIN ; 
 int SIZE_VIO_GET_CHARS ; 
 unsigned long hvc_get_chars (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,unsigned long) ; 

__attribute__((used)) static int filtered_get_chars(uint32_t vtermno, char *buf, int count)
{
	unsigned long got;
	int i;

	/*
	 * Vio firmware will read up to SIZE_VIO_GET_CHARS at its own discretion
	 * so we play safe and avoid the situation where got > count which could
	 * overload the flip buffer.
	 */
	if (count < SIZE_VIO_GET_CHARS)
		return -EAGAIN;

	got = hvc_get_chars(vtermno, buf, count);

	/*
	 * Work around a HV bug where it gives us a null
	 * after every \r.  -- paulus
	 */
	for (i = 1; i < got; ++i) {
		if (buf[i] == 0 && buf[i-1] == '\r') {
			--got;
			if (i < got)
				memmove(&buf[i], &buf[i+1],
					got - i);
		}
	}
	return got;
}