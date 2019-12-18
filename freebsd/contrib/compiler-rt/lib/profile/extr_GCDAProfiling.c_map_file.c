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
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileMapping (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWORD_HI (scalar_t__) ; 
 int /*<<< orphan*/  DWORD_LO (scalar_t__) ; 
 int /*<<< orphan*/  FILE_MAP_WRITE ; 
 char* GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAP_FILE ; 
 int MAP_SHARED ; 
 void* MapViewOfFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SEEK_END ; 
 scalar_t__ _get_osfhandle (int) ; 
 int errno ; 
 int fd ; 
 scalar_t__ file_size ; 
 char* filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 scalar_t__ ftell (int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ ,scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mmap_handle ; 
 int /*<<< orphan*/  output_file ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 void* write_buffer ; 

__attribute__((used)) static int map_file() {
  fseek(output_file, 0L, SEEK_END);
  file_size = ftell(output_file);

  /* A size of 0 is invalid to `mmap'. Return a fail here, but don't issue an
   * error message because it should "just work" for the user. */
  if (file_size == 0)
    return -1;

#if defined(_WIN32)
  HANDLE mmap_fd;
  if (fd == -1)
    mmap_fd = INVALID_HANDLE_VALUE;
  else
    mmap_fd = (HANDLE)_get_osfhandle(fd);

  mmap_handle = CreateFileMapping(mmap_fd, NULL, PAGE_READWRITE, DWORD_HI(file_size), DWORD_LO(file_size), NULL);
  if (mmap_handle == NULL) {
    fprintf(stderr, "profiling: %s: cannot create file mapping: %lu\n",
            filename, GetLastError());
    return -1;
  }

  write_buffer = MapViewOfFile(mmap_handle, FILE_MAP_WRITE, 0, 0, file_size);
  if (write_buffer == NULL) {
    fprintf(stderr, "profiling: %s: cannot map: %lu\n", filename,
            GetLastError());
    CloseHandle(mmap_handle);
    return -1;
  }
#else
  write_buffer = mmap(0, file_size, PROT_READ | PROT_WRITE,
                      MAP_FILE | MAP_SHARED, fd, 0);
  if (write_buffer == (void *)-1) {
    int errnum = errno;
    fprintf(stderr, "profiling: %s: cannot map: %s\n", filename,
            strerror(errnum));
    return -1;
  }
#endif

  return 0;
}