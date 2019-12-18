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
struct ar_hdr {char* ar_name; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 size_t ar_maxnamelen (int /*<<< orphan*/ *) ; 
 char ar_padchar (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 void* strrchr (char const*,char) ; 

void
bfd_gnu_truncate_arname (bfd *abfd, const char *pathname, char *arhdr)
{
  struct ar_hdr *hdr = (struct ar_hdr *) arhdr;
  size_t length;
  const char *filename = strrchr (pathname, '/');
  size_t maxlen = ar_maxnamelen (abfd);

#ifdef HAVE_DOS_BASED_FILE_SYSTEM
  {
    /* We could have foo/bar\\baz, or foo\\bar, or d:bar.  */
    char *bslash = strrchr (pathname, '\\');
    if (filename == NULL || (bslash != NULL && bslash > filename))
      filename = bslash;
    if (filename == NULL && pathname[0] != '\0' && pathname[1] == ':')
      filename = pathname + 1;
  }
#endif

  if (filename == NULL)
    filename = pathname;
  else
    ++filename;

  length = strlen (filename);

  if (length <= maxlen)
    memcpy (hdr->ar_name, filename, length);
  else
    {				/* pathname: meet procrustes */
      memcpy (hdr->ar_name, filename, maxlen);
      if ((filename[length - 2] == '.') && (filename[length - 1] == 'o'))
	{
	  hdr->ar_name[maxlen - 2] = '.';
	  hdr->ar_name[maxlen - 1] = 'o';
	}
      length = maxlen;
    }

  if (length < 16)
    (hdr->ar_name)[length] = ar_padchar (abfd);
}