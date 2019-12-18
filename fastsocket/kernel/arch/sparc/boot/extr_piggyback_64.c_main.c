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
 scalar_t__ lseek (int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ *,int) ; 
 unsigned int write (int,char*,unsigned int) ; 

int main(int argc,char **argv)
{
	char buffer [1024], *q, *r;
	unsigned int i, j, k, start, end, offset;
	FILE *map;
	struct stat s;
	int image, tail;
	
	start = end = 0;
	if (stat (argv[3], &s) < 0) die (argv[3]);
	map = fopen (argv[2], "r");
	if (!map) die(argv[2]);
	while (fgets (buffer, 1024, map)) {
		if (!strcmp (buffer + 19, "_start\n"))
		start = strtoul (buffer + 8, NULL, 16);
		else if (!strcmp (buffer + 19, "_end\n"))
		end = strtoul (buffer + 8, NULL, 16);
	}
	fclose (map);
	if ((image = open(argv[1],O_RDWR)) < 0) die(argv[1]);
	if (read(image,buffer,512) != 512) die(argv[1]);
	if (!memcmp (buffer, "\177ELF", 4)) {
		unsigned int *p = (unsigned int *)(buffer + *(unsigned int *)(buffer + 28));
		
		i = p[1] + *(unsigned int *)(buffer + 24) - p[2];
		if (lseek(image,i,0) < 0) die("lseek");
		if (read(image,buffer,512) != 512) die(argv[1]);
		j = 0;
	} else if (*(unsigned int *)buffer == 0x01030107) {
		i = j = 32;
	} else {
		fprintf (stderr, "Not ELF nor a.out. Don't blame me.\n");
		exit(1);
	}
	k = i;
	if (j == 32 && buffer[40] == 'H' && buffer[41] == 'd' && buffer[42] == 'r' && buffer[43] == 'S') {
		offset = 40 + 10;
	} else {
		i += ((*(unsigned short *)(buffer + j + 2))<<2) - 512;
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
	}
	if (lseek(image, offset, 0) < 0) die ("lseek");
	*(unsigned *)buffer = 0;
	*(unsigned *)(buffer + 4) = 0x01000000;
	*(unsigned *)(buffer + 8) = ((end + 32 + 8191) & ~8191);
	*(unsigned *)(buffer + 12) = s.st_size;
	if (write(image,buffer+2,14) != 14) die (argv[1]);
	if (lseek(image, 4, 0) < 0) die ("lseek");
	*(unsigned *)buffer = ((end + 32 + 8191) & ~8191) - (start & ~0x3fffffUL) + s.st_size;
	*(unsigned *)(buffer + 4) = 0;
	*(unsigned *)(buffer + 8) = 0;
	if (write(image,buffer,12) != 12) die (argv[1]);
	if (lseek(image, k - start + ((end + 32 + 8191) & ~8191), 0) < 0) die ("lseek");
	if ((tail = open(argv[3],O_RDONLY)) < 0) die(argv[3]);
	while ((i = read (tail,buffer,1024)) > 0)
		if (write(image,buffer,i) != i) die (argv[1]);
	if (close(image) < 0) die("close");
	if (close(tail) < 0) die("close");
    	return 0;
}