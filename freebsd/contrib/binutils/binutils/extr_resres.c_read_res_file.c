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
typedef  int /*<<< orphan*/  windres_bfd ;
typedef  scalar_t__ rc_uint_type ;
typedef  int /*<<< orphan*/  rc_res_directory ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  WR_KIND_BFD_BIN_B ; 
 int /*<<< orphan*/  WR_KIND_BFD_BIN_L ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_fatal (char*) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 char const* filename ; 
 scalar_t__ get_file_size (char const*) ; 
 int /*<<< orphan*/  probe_binary (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ read_resource_entry (int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/ * resources ; 
 int /*<<< orphan*/  set_windres_bfd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_windres_bfd_endianess (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_null_resource (int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 
 scalar_t__ target_is_bigendian ; 
 int /*<<< orphan*/ * windres_open_as_binary (char const*,int) ; 

rc_res_directory *
read_res_file (const char *fn)
{
  rc_uint_type off, flen;
  windres_bfd wrbfd;
  bfd *abfd;
  asection *sec;
  filename = fn;

  flen = (rc_uint_type) get_file_size (filename);
  if (! flen)
    fatal ("can't open '%s' for input.", filename);
  abfd = windres_open_as_binary (filename, 1);
  sec = bfd_get_section_by_name (abfd, ".data");
  if (sec == NULL)
    bfd_fatal ("bfd_get_section_by_name");
  set_windres_bfd (&wrbfd, abfd, sec,
		   (target_is_bigendian ? WR_KIND_BFD_BIN_B
					: WR_KIND_BFD_BIN_L));
  off = 0;

  if (! probe_binary (&wrbfd, flen))
    set_windres_bfd_endianess (&wrbfd, ! target_is_bigendian);

  skip_null_resource (&wrbfd, &off, flen);

  while (read_resource_entry (&wrbfd, &off, flen))
    ;

  bfd_close (abfd);

  return resources;
}