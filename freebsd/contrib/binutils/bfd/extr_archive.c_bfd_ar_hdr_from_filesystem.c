#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mtime; int st_uid; int st_gid; int st_mode; int st_size; } ;
struct bfd_in_memory {int size; } ;
struct areltdata {int parsed_size; char* arch_header; } ;
struct ar_hdr {int /*<<< orphan*/  ar_fmag; int /*<<< orphan*/  ar_size; int /*<<< orphan*/  ar_mode; int /*<<< orphan*/  ar_gid; int /*<<< orphan*/  ar_uid; int /*<<< orphan*/  ar_date; } ;
typedef  int bfd_size_type ;
struct TYPE_5__ {int flags; struct bfd_in_memory* iostream; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  ARFMAG ; 
 int BFD_IN_MEMORY ; 
 int /*<<< orphan*/  _bfd_ar_spacepad (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 struct areltdata* bfd_zalloc (TYPE_1__*,int) ; 
 int getgid () ; 
 int getuid () ; 
 int /*<<< orphan*/  hpux_uid_gid_encode (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ar_hdr*,char,int) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  time (int*) ; 

__attribute__((used)) static struct areltdata *
bfd_ar_hdr_from_filesystem (bfd *abfd, const char *filename, bfd *member)
{
  struct stat status;
  struct areltdata *ared;
  struct ar_hdr *hdr;
  bfd_size_type amt;

  if (member && (member->flags & BFD_IN_MEMORY) != 0)
    {
      /* Assume we just "made" the member, and fake it.  */
      struct bfd_in_memory *bim = member->iostream;
      time (&status.st_mtime);
      status.st_uid = getuid ();
      status.st_gid = getgid ();
      status.st_mode = 0644;
      status.st_size = bim->size;
    }
  else if (stat (filename, &status) != 0)
    {
      bfd_set_error (bfd_error_system_call);
      return NULL;
    }

  amt = sizeof (struct ar_hdr) + sizeof (struct areltdata);
  ared = bfd_zalloc (abfd, amt);
  if (ared == NULL)
    return NULL;
  hdr = (struct ar_hdr *) (((char *) ared) + sizeof (struct areltdata));

  /* ar headers are space padded, not null padded!  */
  memset (hdr, ' ', sizeof (struct ar_hdr));

  _bfd_ar_spacepad (hdr->ar_date, sizeof (hdr->ar_date), "%-12ld",
                    status.st_mtime);
#ifdef HPUX_LARGE_AR_IDS
  /* HP has a very "special" way to handle UID/GID's with numeric values
     > 99999.  */
  if (status.st_uid > 99999)
    hpux_uid_gid_encode (hdr->ar_uid, (long) status.st_uid);
  else
#endif
    _bfd_ar_spacepad (hdr->ar_uid, sizeof (hdr->ar_uid), "%ld",
                      status.st_uid);
#ifdef HPUX_LARGE_AR_IDS
  /* HP has a very "special" way to handle UID/GID's with numeric values
     > 99999.  */
  if (status.st_gid > 99999)
    hpux_uid_gid_encode (hdr->ar_gid, (long) status.st_gid);
  else
#endif
    _bfd_ar_spacepad (hdr->ar_gid, sizeof (hdr->ar_gid), "%ld",
                      status.st_gid);
  _bfd_ar_spacepad (hdr->ar_mode, sizeof (hdr->ar_mode), "%-8lo",
                    status.st_mode);
  _bfd_ar_spacepad (hdr->ar_size, sizeof (hdr->ar_size), "%-10ld",
                    status.st_size);
  memcpy (hdr->ar_fmag, ARFMAG, 2);
  ared->parsed_size = status.st_size;
  ared->arch_header = (char *) hdr;

  return ared;
}