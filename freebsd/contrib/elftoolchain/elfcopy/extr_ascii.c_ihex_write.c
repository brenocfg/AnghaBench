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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int _LINE_BUFSZ ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ write (int,char*,int) ; 
 int /*<<< orphan*/  write_num (char*,int*,int const,int,int*) ; 

__attribute__((used)) static void
ihex_write(int ofd, int type, uint64_t addr, uint64_t num, const void *buf,
    size_t sz)
{
	char line[_LINE_BUFSZ];
	const uint8_t *p, *pe;
	int len, checksum;

	if (sz > 16)
		errx(EXIT_FAILURE, "Internal: ihex_write() sz too big");
	checksum = 0;
	line[0] = ':';
	len = 1;
	write_num(line, &len, sz, 1, &checksum);
	write_num(line, &len, addr, 2, &checksum);
	write_num(line, &len, type, 1, &checksum);
	if (sz > 0) {
		if (buf != NULL) {
			for (p = buf, pe = p + sz; p < pe; p++)
				write_num(line, &len, *p, 1, &checksum);
		} else
			write_num(line, &len, num, sz, &checksum);
	}
	write_num(line, &len, (~checksum + 1) & 0xFF, 1, NULL);
	line[len++] = '\r';
	line[len++] = '\n';
	if (write(ofd, line, len) != (ssize_t) len)
		err(EXIT_FAILURE, "write failed");
}