#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
struct TYPE_3__ {scalar_t__ data_size; int header_size; } ;
typedef  TYPE_1__ res_hdr ;
typedef  int rc_uint_type ;

/* Variables and functions */
 int BIN_RES_HDR_SIZE ; 
 char* filename ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* program_name ; 
 int /*<<< orphan*/  read_res_data_hdr (int /*<<< orphan*/ *,int*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ target_is_bigendian ; 
 int /*<<< orphan*/  xexit (int) ; 

__attribute__((used)) static void
skip_null_resource (windres_bfd *wrbfd, rc_uint_type *off, rc_uint_type omax)
{
  res_hdr reshdr;
  read_res_data_hdr (wrbfd, off, omax, &reshdr);
  if (reshdr.data_size != 0)
    goto skip_err;
  if ((reshdr.header_size != 0x20 && ! target_is_bigendian)
    || (reshdr.header_size != 0x20000000 && target_is_bigendian))
    goto skip_err;

  /* Subtract size of HeaderSize. DataSize has to be zero. */
  off[0] += 0x20 - BIN_RES_HDR_SIZE;
  if (off[0] >= omax)
    goto skip_err;

  return;

skip_err:
  fprintf (stderr, "%s: %s: Not a valid WIN32 resource file\n", program_name,
	   filename);
  xexit (1);
}