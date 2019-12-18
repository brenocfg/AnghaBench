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

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FlushViewOfFile (int /*<<< orphan*/ *,scalar_t__) ; 
 char* GetLastError () ; 
 int /*<<< orphan*/  MS_SYNC ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/ *) ; 
 int errno ; 
 scalar_t__ file_size ; 
 char* filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/ * mmap_handle ; 
 int msync (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/ * write_buffer ; 

__attribute__((used)) static void unmap_file() {
#if defined(_WIN32)
  if (!FlushViewOfFile(write_buffer, file_size)) {
    fprintf(stderr, "profiling: %s: cannot flush mapped view: %lu\n", filename,
            GetLastError());
  }

  if (!UnmapViewOfFile(write_buffer)) {
    fprintf(stderr, "profiling: %s: cannot unmap mapped view: %lu\n", filename,
            GetLastError());
  }

  if (!CloseHandle(mmap_handle)) {
    fprintf(stderr, "profiling: %s: cannot close file mapping handle: %lu\n",
            filename, GetLastError());
  }

  mmap_handle = NULL;
#else
  if (msync(write_buffer, file_size, MS_SYNC) == -1) {
    int errnum = errno;
    fprintf(stderr, "profiling: %s: cannot msync: %s\n", filename,
            strerror(errnum));
  }

  /* We explicitly ignore errors from unmapping because at this point the data
   * is written and we don't care.
   */
  (void)munmap(write_buffer, file_size);
#endif

  write_buffer = NULL;
  file_size = 0;
}