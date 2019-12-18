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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CharLowerBuff (char*,scalar_t__) ; 
 scalar_t__ GetFullPathName (char const*,int,char*,char**) ; 
 int MAX_PATH ; 
 int REALPATH_LIMIT ; 
 int /*<<< orphan*/  _PC_PATH_MAX ; 
 char* canonicalize_file_name (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (long) ; 
 long pathconf (char*,int /*<<< orphan*/ ) ; 
 void* realpath (char const*,char*) ; 
 char* strdup (char const*) ; 

char *
lrealpath (const char *filename)
{
  /* Method 1: The system has a compile time upper bound on a filename
     path.  Use that and realpath() to canonicalize the name.  This is
     the most common case.  Note that, if there isn't a compile time
     upper bound, you want to avoid realpath() at all costs.  */
#if defined(REALPATH_LIMIT)
  {
    char buf[REALPATH_LIMIT];
    const char *rp = realpath (filename, buf);
    if (rp == NULL)
      rp = filename;
    return strdup (rp);
  }
#endif /* REALPATH_LIMIT */

  /* Method 2: The host system (i.e., GNU) has the function
     canonicalize_file_name() which malloc's a chunk of memory and
     returns that, use that.  */
#if defined(HAVE_CANONICALIZE_FILE_NAME)
  {
    char *rp = canonicalize_file_name (filename);
    if (rp == NULL)
      return strdup (filename);
    else
      return rp;
  }
#endif

  /* Method 3: Now we're getting desperate!  The system doesn't have a
     compile time buffer size and no alternative function.  Query the
     OS, using pathconf(), for the buffer limit.  Care is needed
     though, some systems do not limit PATH_MAX (return -1 for
     pathconf()) making it impossible to pass a correctly sized buffer
     to realpath() (it could always overflow).  On those systems, we
     skip this.  */
#if defined (HAVE_REALPATH) && defined (HAVE_UNISTD_H)
  {
    /* Find out the max path size.  */
    long path_max = pathconf ("/", _PC_PATH_MAX);
    if (path_max > 0)
      {
	/* PATH_MAX is bounded.  */
	char *buf, *rp, *ret;
	buf = (char *) malloc (path_max);
	if (buf == NULL)
	  return NULL;
	rp = realpath (filename, buf);
	ret = strdup (rp ? rp : filename);
	free (buf);
	return ret;
      }
  }
#endif

  /* The MS Windows method.  If we don't have realpath, we assume we
     don't have symlinks and just canonicalize to a Windows absolute
     path.  GetFullPath converts ../ and ./ in relative paths to
     absolute paths, filling in current drive if one is not given
     or using the current directory of a specified drive (eg, "E:foo").
     It also converts all forward slashes to back slashes.  */
#if defined (_WIN32)
  {
    char buf[MAX_PATH];
    char* basename;
    DWORD len = GetFullPathName (filename, MAX_PATH, buf, &basename);
    if (len == 0 || len > MAX_PATH - 1)
      return strdup (filename);
    else
      {
	/* The file system is case-preserving but case-insensitive,
	   Canonicalize to lowercase, using the codepage associated
	   with the process locale.  */
        CharLowerBuff (buf, len);
        return strdup (buf);
      }
  }
#endif

  /* This system is a lost cause, just duplicate the filename.  */
  return strdup (filename);
}