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
typedef  int /*<<< orphan*/  tchar ;
struct stat {size_t st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  _EXPAT_read_req_t ;
typedef  scalar_t__ _EXPAT_read_count_t ;

/* Variables and functions */
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T (char*) ; 
 size_t XML_MAX_CHUNK_LEN ; 
 scalar_t__ _EXPAT_read (int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  stderr ; 
 int topen (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  tperror (int /*<<< orphan*/  const*) ; 

int
filemap(const tchar *name,
        void (*processor)(const void *, size_t, const tchar *, void *arg),
        void *arg)
{
  size_t nbytes;
  int fd;
  _EXPAT_read_count_t n;
  struct stat sb;
  void *p;

  fd = topen(name, O_RDONLY|O_BINARY);
  if (fd < 0) {
    tperror(name);
    return 0;
  }
  if (fstat(fd, &sb) < 0) {
    tperror(name);
    close(fd);
    return 0;
  }
  if (!S_ISREG(sb.st_mode)) {
    ftprintf(stderr, T("%s: not a regular file\n"), name);
    close(fd);
    return 0;
  }
  if (sb.st_size > XML_MAX_CHUNK_LEN) {
    close(fd);
    return 2;  /* Cannot be passed to XML_Parse in one go */
  }

  nbytes = sb.st_size;
  /* malloc will return NULL with nbytes == 0, handle files with size 0 */
  if (nbytes == 0) {
    static const char c = '\0';
    processor(&c, 0, name, arg);
    close(fd);
    return 1;
  }
  p = malloc(nbytes);
  if (!p) {
    ftprintf(stderr, T("%s: out of memory\n"), name);
    close(fd);
    return 0;
  }
  n = _EXPAT_read(fd, p, (_EXPAT_read_req_t)nbytes);
  if (n < 0) {
    tperror(name);
    free(p);
    close(fd);
    return 0;
  }
  if (n != (_EXPAT_read_count_t)nbytes) {
    ftprintf(stderr, T("%s: read unexpected number of bytes\n"), name);
    free(p);
    close(fd);
    return 0;
  }
  processor(p, nbytes, name, arg);
  free(p);
  close(fd);
  return 1;
}