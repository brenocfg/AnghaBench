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
 int /*<<< orphan*/  MAXPATHLEN ; 
 char* getcwd (char*,int /*<<< orphan*/ ) ; 
 char* getwd (char*) ; 
 int /*<<< orphan*/  transform_dir (char*) ; 
 int /*<<< orphan*/  xstrlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static char *
getawd(char *path, size_t l)
{
#ifdef HAVE_GETCWD
  char *wd = getcwd(path, MAXPATHLEN);
#else /* not HAVE_GETCWD */
  char *wd = getwd(path);
#endif /* not HAVE_GETCWD */

  if (wd == NULL) {
    return NULL;
  }
  xstrlcpy(path, transform_dir(wd), l);
  return path;
}