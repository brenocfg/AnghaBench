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
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  unsigned int bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int CHUNK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TOHEX (char*,unsigned int) ; 
 int /*<<< orphan*/  TRUE ; 
 size_t bfd_bwrite (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
ihex_write_record (bfd *abfd,
		   size_t count,
		   unsigned int addr,
		   unsigned int type,
		   bfd_byte *data)
{
  static const char digs[] = "0123456789ABCDEF";
  char buf[9 + CHUNK * 2 + 4];
  char *p;
  unsigned int chksum;
  unsigned int i;
  size_t total;

#define TOHEX(buf, v) \
  ((buf)[0] = digs[((v) >> 4) & 0xf], (buf)[1] = digs[(v) & 0xf])

  buf[0] = ':';
  TOHEX (buf + 1, count);
  TOHEX (buf + 3, (addr >> 8) & 0xff);
  TOHEX (buf + 5, addr & 0xff);
  TOHEX (buf + 7, type);

  chksum = count + addr + (addr >> 8) + type;

  for (i = 0, p = buf + 9; i < count; i++, p += 2, data++)
    {
      TOHEX (p, *data);
      chksum += *data;
    }

  TOHEX (p, (- chksum) & 0xff);
  p[2] = '\r';
  p[3] = '\n';

  total = 9 + count * 2 + 4;
  if (bfd_bwrite (buf, (bfd_size_type) total, abfd) != total)
    return FALSE;

  return TRUE;
}