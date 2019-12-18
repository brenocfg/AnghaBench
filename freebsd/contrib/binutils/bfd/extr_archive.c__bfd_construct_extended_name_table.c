#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ar_hdr {scalar_t__* ar_name; } ;
typedef  scalar_t__ bfd_size_type ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_10__ {int /*<<< orphan*/  filename; struct TYPE_10__* archive_next; struct TYPE_10__* archive_head; TYPE_1__* xvec; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_9__ {unsigned int ar_max_namelen; } ;

/* Variables and functions */
 int BFD_TRADITIONAL_FORMAT ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _bfd_ar_spacepad (scalar_t__*,unsigned int,char*,int) ; 
 scalar_t__ ar_padchar (TYPE_2__*) ; 
 struct ar_hdr* arch_hdr (TYPE_2__*) ; 
 int bfd_get_file_flags (TYPE_2__*) ; 
 char* bfd_zalloc (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,unsigned int) ; 
 char* normalize (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 unsigned int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,scalar_t__*,unsigned int) ; 

bfd_boolean
_bfd_construct_extended_name_table (bfd *abfd,
				    bfd_boolean trailing_slash,
				    char **tabloc,
				    bfd_size_type *tablen)
{
  unsigned int maxname = abfd->xvec->ar_max_namelen;
  bfd_size_type total_namelen = 0;
  bfd *current;
  char *strptr;

  *tablen = 0;

  /* Figure out how long the table should be.  */
  for (current = abfd->archive_head;
       current != NULL;
       current = current->archive_next)
    {
      const char *normal;
      unsigned int thislen;

      normal = normalize (current, current->filename);
      if (normal == NULL)
	return FALSE;

      thislen = strlen (normal);

      if (thislen > maxname
	  && (bfd_get_file_flags (abfd) & BFD_TRADITIONAL_FORMAT) != 0)
	thislen = maxname;

      if (thislen > maxname)
	{
	  /* Add one to leave room for \n.  */
	  total_namelen += thislen + 1;
	  if (trailing_slash)
	    {
	      /* Leave room for trailing slash.  */
	      ++total_namelen;
	    }
	}
      else
	{
	  struct ar_hdr *hdr = arch_hdr (current);
	  if (strncmp (normal, hdr->ar_name, thislen) != 0
	      || (thislen < sizeof hdr->ar_name
		  && hdr->ar_name[thislen] != ar_padchar (current)))
	    {
	      /* Must have been using extended format even though it
	         didn't need to.  Fix it to use normal format.  */
	      memcpy (hdr->ar_name, normal, thislen);
	      if (thislen < maxname
		  || (thislen == maxname && thislen < sizeof hdr->ar_name))
		hdr->ar_name[thislen] = ar_padchar (current);
	    }
	}
    }

  if (total_namelen == 0)
    return TRUE;

  *tabloc = bfd_zalloc (abfd, total_namelen);
  if (*tabloc == NULL)
    return FALSE;

  *tablen = total_namelen;
  strptr = *tabloc;

  for (current = abfd->archive_head;
       current != NULL;
       current = current->archive_next)
    {
      const char *normal;
      unsigned int thislen;

      normal = normalize (current, current->filename);
      if (normal == NULL)
	return FALSE;

      thislen = strlen (normal);
      if (thislen > maxname)
	{
	  /* Works for now; may need to be re-engineered if we
	     encounter an oddball archive format and want to
	     generalise this hack.  */
	  struct ar_hdr *hdr = arch_hdr (current);
	  strcpy (strptr, normal);
	  if (! trailing_slash)
	    strptr[thislen] = '\012';
	  else
	    {
	      strptr[thislen] = '/';
	      strptr[thislen + 1] = '\012';
	    }
	  hdr->ar_name[0] = ar_padchar (current);
          _bfd_ar_spacepad (hdr->ar_name + 1, maxname - 1, "%-ld",
                            strptr - *tabloc);
	  strptr += thislen + 1;
	  if (trailing_slash)
	    ++strptr;
	}
    }

  return TRUE;
}