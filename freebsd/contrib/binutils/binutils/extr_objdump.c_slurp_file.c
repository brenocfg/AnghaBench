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
struct stat {size_t st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int getpagesize () ; 
 char* malloc (size_t) ; 
 char* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,size_t) ; 

__attribute__((used)) static const char *
slurp_file (const char *fn, size_t *size)
{
#ifdef HAVE_MMAP
  int ps = getpagesize ();
  size_t msize;
#endif
  const char *map;
  struct stat st;
  int fd = open (fn, O_RDONLY);

  if (fd < 0)
    return NULL;
  if (fstat (fd, &st) < 0)
    return NULL;
  *size = st.st_size;
#ifdef HAVE_MMAP
  msize = (*size + ps - 1) & ~(ps - 1);
  map = mmap (NULL, msize, PROT_READ, MAP_SHARED, fd, 0);
  if (map != (char *)-1L)
    {
      close(fd);
      return map; 
    }
#endif
  map = malloc (*size);
  if (!map || (size_t) read (fd, (char *)map, *size) != *size) 
    { 
      free ((void *)map);
      map = NULL;
    }
  close (fd);
  return map; 
}