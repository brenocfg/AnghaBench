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
 int HDR_LENGTH ; 

__attribute__((used)) static int
mips_cksum (const unsigned char *hdr, const unsigned char *data, int len)
{
  const unsigned char *p;
  int c;
  int cksum;

  cksum = 0;

  /* The initial SYN is not included in the checksum.  */
  c = HDR_LENGTH - 1;
  p = hdr + 1;
  while (c-- != 0)
    cksum += *p++;

  c = len;
  p = data;
  while (c-- != 0)
    cksum += *p++;

  return cksum;
}