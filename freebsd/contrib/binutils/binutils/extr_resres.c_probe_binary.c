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
 int /*<<< orphan*/  read_res_data_hdr (int /*<<< orphan*/ *,int*,int,TYPE_1__*) ; 
 scalar_t__ target_is_bigendian ; 

__attribute__((used)) static int
probe_binary (windres_bfd *wrbfd, rc_uint_type omax)
{
  rc_uint_type off;
  res_hdr reshdr;

  off = 0;
  read_res_data_hdr (wrbfd, &off, omax, &reshdr);
  if (reshdr.data_size != 0)
    return 1;
  if ((reshdr.header_size != 0x20 && ! target_is_bigendian)
      || (reshdr.header_size != 0x20000000 && target_is_bigendian))
    return 1;

  /* Subtract size of HeaderSize. DataSize has to be zero. */
  off += 0x20 - BIN_RES_HDR_SIZE;
  if ((off + BIN_RES_HDR_SIZE) >= omax)
    return 1;
  read_res_data_hdr (wrbfd, &off, omax, &reshdr);
  /* off is advanced by BIN_RES_HDR_SIZE in read_res_data_hdr()
     which is part of reshdr.header_size. We shouldn't take it
     into account twice.  */
  if ((off - BIN_RES_HDR_SIZE + reshdr.data_size + reshdr.header_size) > omax)
    return 0;
  return 1;
}