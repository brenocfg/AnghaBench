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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ldm_error (char*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static int ldm_get_vstr (const u8 *block, u8 *buffer, int buflen)
{
	int length;

	BUG_ON (!block || !buffer);

	length = block[0];
	if (length >= buflen) {
		ldm_error ("Truncating string %d -> %d.", length, buflen);
		length = buflen - 1;
	}
	memcpy (buffer, block + 1, length);
	buffer[length] = 0;
	return length;
}