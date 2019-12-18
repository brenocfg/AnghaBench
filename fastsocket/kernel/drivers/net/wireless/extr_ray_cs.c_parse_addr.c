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
typedef  int UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRLEN ; 
 int asc_to_int (char) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static int parse_addr(char *in_str, UCHAR *out)
{
	int len;
	int i, j, k;
	int status;

	if (in_str == NULL)
		return 0;
	if ((len = strlen(in_str)) < 2)
		return 0;
	memset(out, 0, ADDRLEN);

	status = 1;
	j = len - 1;
	if (j > 12)
		j = 12;
	i = 5;

	while (j > 0) {
		if ((k = asc_to_int(in_str[j--])) != -1)
			out[i] = k;
		else
			return 0;

		if (j == 0)
			break;
		if ((k = asc_to_int(in_str[j--])) != -1)
			out[i] += k << 4;
		else
			return 0;
		if (!i--)
			break;
	}
	return status;
}