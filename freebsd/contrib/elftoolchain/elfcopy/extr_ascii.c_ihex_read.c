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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */
 scalar_t__ read_num (char const*,int*,int*,int,int*) ; 

__attribute__((used)) static int
ihex_read(const char *line, char *type, uint64_t *addr, uint64_t *num,
    uint8_t *data, size_t *sz)
{
	uint64_t count, _checksum;
	int checksum, i, len;

	*sz = 0;
	checksum = 0;
	len = 1;
	if (read_num(line, &len, &count, 1, &checksum) < 0)
		return (-1);
	if (read_num(line, &len, addr, 2, &checksum) < 0)
		return (-1);
	if (line[len++] != '0')
		return (-1);
	*type = line[len++];
	checksum += *type - '0';
	switch (*type) {
	case '0':
		for (i = 0; (uint64_t) i < count; i++) {
			if (read_num(line, &len, num, 1, &checksum) < 0)
				return (-1);
			data[i] = (uint8_t) *num;
		}
		*sz = count;
		break;
	case '1':
		if (count != 0)
			return (-1);
		break;
	case '2':
	case '4':
		if (count != 2)
			return (-1);
		if (read_num(line, &len, num, 2, &checksum) < 0)
			return (-1);
		break;
	case '3':
	case '5':
		if (count != 4)
			return (-1);
		if (read_num(line, &len, num, 4, &checksum) < 0)
			return (-1);
		break;
	default:
		return (-1);
	}

	if (read_num(line, &len, &_checksum, 1, &checksum) < 0)
		return (-1);

	if ((checksum & 0xFF) != 0) {
		return (-1);
	}

	return (0);
}