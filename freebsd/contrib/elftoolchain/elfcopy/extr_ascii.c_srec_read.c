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
typedef  scalar_t__ uint8_t ;
typedef  size_t uint64_t ;

/* Variables and functions */
 scalar_t__ read_num (char const*,int*,size_t*,int,int*) ; 

__attribute__((used)) static int
srec_read(const char *line, char *type, uint64_t *addr, uint8_t *data,
    size_t *sz)
{
	uint64_t count, _checksum, num;
	size_t addr_sz;
	int checksum, i, len;

	checksum = 0;
	len = 2;
	if (read_num(line, &len, &count, 1, &checksum) < 0)
		return (-1);
	*type = line[1];
	switch (*type) {
	case '0':
	case '1':
	case '5':
	case '9':
		addr_sz = 2;
		break;
	case '2':
	case '8':
		addr_sz = 3;
		break;
	case '3':
	case '7':
		addr_sz = 4;
		break;
	default:
		return (-1);
	}

	if (read_num(line, &len, addr, addr_sz, &checksum) < 0)
		return (-1);

	count -= addr_sz + 1;
	if (*type >= '0' && *type <= '3') {
		for (i = 0; (uint64_t) i < count; i++) {
			if (read_num(line, &len, &num, 1, &checksum) < 0)
				return -1;
			data[i] = (uint8_t) num;
		}
		*sz = count;
	} else
		*sz = 0;

	if (read_num(line, &len, &_checksum, 1, NULL) < 0)
		return (-1);

	if ((int) _checksum != (~checksum & 0xFF))
		return (-1);

	return (0);
}