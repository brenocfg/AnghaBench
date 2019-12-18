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
struct stat {scalar_t__ st_size; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 char* malloc (size_t) ; 
 char* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (char*,size_t) ; 
 scalar_t__ read (int,char*,size_t) ; 
 scalar_t__ write (int,char*,size_t) ; 

int
elftc_copyfile(int ifd, int ofd)
{
	size_t file_size, n;
	int buf_mmapped;
	struct stat sb;
	char *b, *buf;
	ssize_t nr, nw;

	/* Determine the input file's size. */
	if (fstat(ifd, &sb) < 0)
		return (-1);

	/* Skip files without content. */
	if (sb.st_size == 0)
		return (0);

	buf = NULL;
	buf_mmapped = 0;
	file_size = (size_t) sb.st_size;

#if	ELFTC_HAVE_MMAP
	/*
	 * Prefer mmap() if it is available.
	 */
	buf = mmap(NULL, file_size, PROT_READ, MAP_SHARED, ifd, (off_t) 0);
	if (buf != MAP_FAILED)
		buf_mmapped = 1;
	else
		buf = NULL;
#endif

	/*
	 * If mmap() is not available, or if the mmap() operation
	 * failed, allocate a buffer, and read in input data.
	 */
	if (buf_mmapped == false) {
		if ((buf = malloc(file_size)) == NULL)
			return (-1);
		b = buf;
		for (n = file_size; n > 0; n -= (size_t) nr, b += nr) {
			if ((nr = read(ifd, b, n)) < 0) {
				free(buf);
				return (-1);
			}
		}
	}

	/*
	 * Write data to the output file descriptor.
	 */
	for (n = file_size, b = buf; n > 0; n -= (size_t) nw, b += nw)
		if ((nw = write(ofd, b, n)) <= 0)
			break;

	/* Release the input buffer. */
#if	ELFTC_HAVE_MMAP
	if (buf_mmapped && munmap(buf, file_size) < 0)
		return (-1);
#endif

	if (!buf_mmapped)
		free(buf);

	return (n > 0 ? -1 : 0);
}