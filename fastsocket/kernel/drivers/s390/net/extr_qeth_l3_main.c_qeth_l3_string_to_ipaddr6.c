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
typedef  int /*<<< orphan*/  __u8 ;
typedef  char __u16 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qeth_l3_isxdigit (char*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

int qeth_l3_string_to_ipaddr6(const char *buf, __u8 *addr)
{
	const char *end, *end_tmp, *start;
	__u16 *in;
	char num[5];
	int num2, cnt, out, found, save_cnt;
	unsigned short in_tmp[8] = {0, };

	cnt = out = found = save_cnt = num2 = 0;
	end = start = buf;
	in = (__u16 *) addr;
	memset(in, 0, 16);
	while (*end) {
		end = strchr(start, ':');
		if (end == NULL) {
			end = buf + strlen(buf);
			end_tmp = strchr(start, '\n');
			if (end_tmp != NULL)
				end = end_tmp;
			out = 1;
		}
		if ((end - start)) {
			memset(num, 0, 5);
			if ((end - start) > 4)
				return -EINVAL;
			memcpy(num, start, end - start);
			if (!qeth_l3_isxdigit(num))
				return -EINVAL;
			sscanf(start, "%x", &num2);
			if (found)
				in_tmp[save_cnt++] = num2;
			else
				in[cnt++] = num2;
			if (out)
				break;
		} else {
			if (found)
				return -EINVAL;
			found = 1;
		}
		start = ++end;
	}
	if (cnt + save_cnt > 8)
		return -EINVAL;
	cnt = 7;
	while (save_cnt)
		in[cnt--] = in_tmp[--save_cnt];
	return 0;
}