#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_7__ {int e_fd; unsigned int e_flags; scalar_t__ e_kind; scalar_t__ e_cmd; int /*<<< orphan*/  e_byteorder; } ;
typedef  scalar_t__ Elf_Cmd ;
typedef  TYPE_1__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 scalar_t__ ELF_C_RDWR ; 
 scalar_t__ ELF_C_READ ; 
 scalar_t__ ELF_C_WRITE ; 
 scalar_t__ ELF_K_AR ; 
 int /*<<< orphan*/  ELF_K_ELF ; 
 int /*<<< orphan*/  IO ; 
 unsigned int LIBELF_F_RAWFILE_MALLOC ; 
 unsigned int LIBELF_F_RAWFILE_MMAP ; 
 unsigned int LIBELF_F_SPECIAL_FILE ; 
 int /*<<< orphan*/  LIBELF_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  RESOURCE ; 
 int /*<<< orphan*/  S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISSOCK (int /*<<< orphan*/ ) ; 
 TYPE_1__* _libelf_allocate_elf () ; 
 int /*<<< orphan*/  _libelf_init_elf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* _libelf_memory (void*,size_t,int) ; 
 void* _libelf_read_special_file (int,size_t*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  byteorder ; 
 int /*<<< orphan*/  elf_end (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 void* malloc (size_t) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 
 scalar_t__ read (int,void*,size_t) ; 

Elf *
_libelf_open_object(int fd, Elf_Cmd c, int reporterror)
{
	Elf *e;
	void *m;
	mode_t mode;
	size_t fsize;
	struct stat sb;
	unsigned int flags;

	assert(c == ELF_C_READ || c == ELF_C_RDWR || c == ELF_C_WRITE);

	if (fstat(fd, &sb) < 0) {
		LIBELF_SET_ERROR(IO, errno);
		return (NULL);
	}

	mode = sb.st_mode;
	fsize = (size_t) sb.st_size;

	/*
	 * Reject unsupported file types.
	 */
	if (!S_ISREG(mode) && !S_ISCHR(mode) && !S_ISFIFO(mode) &&
	    !S_ISSOCK(mode)) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	/*
	 * For ELF_C_WRITE mode, allocate and return a descriptor.
	 */
	if (c == ELF_C_WRITE) {
		if ((e = _libelf_allocate_elf()) != NULL) {
			_libelf_init_elf(e, ELF_K_ELF);
			e->e_byteorder = LIBELF_PRIVATE(byteorder);
			e->e_fd = fd;
			e->e_cmd = c;
			if (!S_ISREG(mode))
				e->e_flags |= LIBELF_F_SPECIAL_FILE;
		}

		return (e);
	}


	/*
	 * ELF_C_READ and ELF_C_RDWR mode.
	 */
	m = NULL;
	flags = 0;
	if (S_ISREG(mode)) {

		/*
		 * Reject zero length files.
		 */
		if (fsize == 0) {
			LIBELF_SET_ERROR(ARGUMENT, 0);
			return (NULL);
		}

#if	ELFTC_HAVE_MMAP
		/*
		 * Always map regular files in with 'PROT_READ'
		 * permissions.
		 *
		 * For objects opened in ELF_C_RDWR mode, when
		 * elf_update(3) is called, we remove this mapping,
		 * write file data out using write(2), and map the new
		 * contents back.
		 */
		m = mmap(NULL, fsize, PROT_READ, MAP_PRIVATE, fd, (off_t) 0);

		if (m == MAP_FAILED)
			m = NULL;
		else
			flags = LIBELF_F_RAWFILE_MMAP;
#endif

		/*
		 * Fallback to a read() if the call to mmap() failed,
		 * or if mmap() is not available.
		 */
		if (m == NULL) {
			if ((m = malloc(fsize)) == NULL) {
				LIBELF_SET_ERROR(RESOURCE, 0);
				return (NULL);
			}

			if (read(fd, m, fsize) != (ssize_t) fsize) {
				LIBELF_SET_ERROR(IO, errno);
				free(m);
				return (NULL);
			}

			flags = LIBELF_F_RAWFILE_MALLOC;
		}
	} else if ((m = _libelf_read_special_file(fd, &fsize)) != NULL)
		flags = LIBELF_F_RAWFILE_MALLOC | LIBELF_F_SPECIAL_FILE;
	else
		return (NULL);

	if ((e = _libelf_memory(m, fsize, reporterror)) == NULL) {
		assert((flags & LIBELF_F_RAWFILE_MALLOC) ||
		    (flags & LIBELF_F_RAWFILE_MMAP));
		if (flags & LIBELF_F_RAWFILE_MALLOC)
			free(m);
#if	ELFTC_HAVE_MMAP
		else
			(void) munmap(m, fsize);
#endif
		return (NULL);
	}

	/* ar(1) archives aren't supported in RDWR mode. */
	if (c == ELF_C_RDWR && e->e_kind == ELF_K_AR) {
		(void) elf_end(e);
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	e->e_flags |= flags;
	e->e_fd = fd;
	e->e_cmd = c;

	return (e);
}