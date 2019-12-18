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
struct ar_hdr {int /*<<< orphan*/ * ar_name; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int BFD_TRADITIONAL_FORMAT ; 
 int /*<<< orphan*/  abort () ; 
 size_t ar_maxnamelen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ar_padchar (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_bsd_truncate_arname (int /*<<< orphan*/ *,char const*,char*) ; 
 int bfd_get_file_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 char* normalize (int /*<<< orphan*/ *,char const*) ; 
 size_t strlen (char const*) ; 

void
bfd_dont_truncate_arname (bfd *abfd, const char *pathname, char *arhdr)
{
  /* FIXME: This interacts unpleasantly with ar's quick-append option.
     Fortunately ic960 users will never use that option.  Fixing this
     is very hard; fortunately I know how to do it and will do so once
     intel's release is out the door.  */

  struct ar_hdr *hdr = (struct ar_hdr *) arhdr;
  size_t length;
  const char *filename;
  size_t maxlen = ar_maxnamelen (abfd);

  if ((bfd_get_file_flags (abfd) & BFD_TRADITIONAL_FORMAT) != 0)
    {
      bfd_bsd_truncate_arname (abfd, pathname, arhdr);
      return;
    }

  filename = normalize (abfd, pathname);
  if (filename == NULL)
    {
      /* FIXME */
      abort ();
    }

  length = strlen (filename);

  if (length <= maxlen)
    memcpy (hdr->ar_name, filename, length);

  /* Add the padding character if there is room for it.  */
  if (length < maxlen
      || (length == maxlen && length < sizeof hdr->ar_name))
    (hdr->ar_name)[length] = ar_padchar (abfd);
}