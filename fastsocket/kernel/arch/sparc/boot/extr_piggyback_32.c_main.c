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
struct stat {unsigned int st_size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int ld2 (char*) ; 
 int ld4 (char*) ; 
 scalar_t__ lseek (int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  st4 (char*,unsigned int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usage () ; 
 unsigned int write (int,char*,unsigned int) ; 

int main(int argc,char **argv)
{
	static char aout_magic[] = { 0x01, 0x03, 0x01, 0x07 };
	char buffer[1024], *q, *r;
	unsigned int i, j, k, start, end, offset;
	FILE *map;
	struct stat s;
	int image, tail;

	if (argc != 4) usage();
	start = end = 0;
	if (stat (argv[3], &s) < 0) die (argv[3]);
	map = fopen (argv[2], "r");
	if (!map) die(argv[2]);
	while (fgets (buffer, 1024, map)) {
		if (!strcmp (buffer + 8, " T start\n") || !strcmp (buffer + 16, " T start\n"))
			start = strtoul (buffer, NULL, 16);
		else if (!strcmp (buffer + 8, " A _end\n") || !strcmp (buffer + 16, " A _end\n"))
			end = strtoul (buffer, NULL, 16);
	}
	fclose (map);
	if (!start || !end) {
		fprintf (stderr, "Could not determine start and end from System.map\n");
		exit(1);
	}
	if ((image = open(argv[1],O_RDWR)) < 0) die(argv[1]);
	if (read(image,buffer,512) != 512) die(argv[1]);
	if (memcmp (buffer, "\177ELF", 4) == 0) {
		q = buffer + ld4(buffer + 28);
		i = ld4(q + 4) + ld4(buffer + 24) - ld4(q + 8);
		if (lseek(image,i,0) < 0) die("lseek");
		if (read(image,buffer,512) != 512) die(argv[1]);
		j = 0;
	} else if (memcmp(buffer, aout_magic, 4) == 0) {
		i = j = 32;
	} else {
		fprintf (stderr, "Not ELF nor a.out. Don't blame me.\n");
		exit(1);
	}
	k = i;
	i += (ld2(buffer + j + 2)<<2) - 512;
	if (lseek(image,i,0) < 0) die("lseek");
	if (read(image,buffer,1024) != 1024) die(argv[1]);
	for (q = buffer, r = q + 512; q < r; q += 4) {
		if (*q == 'H' && q[1] == 'd' && q[2] == 'r' && q[3] == 'S')
			break;
	}
	if (q == r) {
		fprintf (stderr, "Couldn't find headers signature in the kernel.\n");
		exit(1);
	}
	offset = i + (q - buffer) + 10;
	if (lseek(image, offset, 0) < 0) die ("lseek");

	st4(buffer, 0);
	st4(buffer + 4, 0x01000000);
	st4(buffer + 8, (end + 32 + 4095) & ~4095);
	st4(buffer + 12, s.st_size);

	if (write(image,buffer+2,14) != 14) die (argv[1]);
	if (lseek(image, k - start + ((end + 32 + 4095) & ~4095), 0) < 0) die ("lseek");
	if ((tail = open(argv[3],O_RDONLY)) < 0) die(argv[3]);
	while ((i = read (tail,buffer,1024)) > 0)
		if (write(image,buffer,i) != i) die (argv[1]);
	if (close(image) < 0) die("close");
	if (close(tail) < 0) die("close");
    	return 0;
}