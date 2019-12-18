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
typedef  int /*<<< orphan*/  IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  ixj_write_cid_byte (int /*<<< orphan*/ *,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static int ixj_write_cid_string(IXJ *j, char *s, int checksum)
{
	int cnt;

	for (cnt = 0; cnt < strlen(s); cnt++) {
		ixj_write_cid_byte(j, s[cnt]);
		checksum = (checksum + s[cnt]);
	}
	return checksum;
}