#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
typedef  int /*<<< orphan*/  sign ;
typedef  int rc_uint_type ;
typedef  int /*<<< orphan*/  rc_res_id ;
typedef  int /*<<< orphan*/  rc_res_directory ;
typedef  int bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {struct TYPE_6__* output_section; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int SEC_ALLOC ; 
 int SEC_DATA ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_LOAD ; 
 int /*<<< orphan*/  WR_KIND_BFD_BIN_B ; 
 int /*<<< orphan*/  WR_KIND_BFD_BIN_L ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_fatal (char*) ; 
 TYPE_1__* bfd_make_section (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfd_set_section_size (int /*<<< orphan*/ *,TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  fatal (char*,long,long) ; 
 char const* filename ; 
 int /*<<< orphan*/  set_windres_bfd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_windres_bfd_content (int /*<<< orphan*/ *,int const*,unsigned long,int) ; 
 scalar_t__ target_is_bigendian ; 
 int /*<<< orphan*/ * windres_open_as_binary (char const*,int /*<<< orphan*/ ) ; 
 unsigned long write_res_directory (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int*,int) ; 

void
write_res_file (const char *fn,const rc_res_directory *resdir)
{
  asection *sec;
  rc_uint_type language;
  bfd *abfd;
  windres_bfd wrbfd;
  unsigned long sec_length = 0,sec_length_wrote;
  static const bfd_byte sign[] =
  {0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
   0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  filename = fn;

  abfd = windres_open_as_binary (filename, 0);
  sec = bfd_make_section (abfd, ".data");
  if (sec == NULL)
    bfd_fatal ("bfd_make_section");
  if (! bfd_set_section_flags (abfd, sec,
			       (SEC_HAS_CONTENTS | SEC_ALLOC
			        | SEC_LOAD | SEC_DATA)))
    bfd_fatal ("bfd_set_section_flags");
  /* Requiring this is probably a bug in BFD.  */
  sec->output_section = sec;

  set_windres_bfd (&wrbfd, abfd, sec,
		   (target_is_bigendian ? WR_KIND_BFD_BIN_B
					: WR_KIND_BFD_BIN_L));

  language = -1;
  sec_length = write_res_directory ((windres_bfd *) NULL, 0x20UL, resdir,
				    (const rc_res_id *) NULL,
				    (const rc_res_id *) NULL, &language, 1);
  if (! bfd_set_section_size (abfd, sec, (sec_length + 3) & ~3))
    bfd_fatal ("bfd_set_section_size");
  if ((sec_length & 3) != 0)
    set_windres_bfd_content (&wrbfd, sign, sec_length, 4-(sec_length & 3));
  set_windres_bfd_content (&wrbfd, sign, 0, sizeof (sign));
  language = -1;
  sec_length_wrote = write_res_directory (&wrbfd, 0x20UL, resdir,
					  (const rc_res_id *) NULL,
					  (const rc_res_id *) NULL,
					  &language, 1);
  if (sec_length != sec_length_wrote)
    fatal ("res write failed with different sizes (%lu/%lu).", (long) sec_length,
    	   (long) sec_length_wrote);

  bfd_close (abfd);
  return;
}