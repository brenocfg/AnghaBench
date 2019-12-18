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
typedef  int bfd_vma ;
typedef  int bfd_size_type ;
typedef  unsigned int bfd_byte ;
typedef  int bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int MAXCHUNK ; 
 int /*<<< orphan*/  TOHEX (char*,unsigned int const,unsigned int) ; 
 int bfd_bwrite (void*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
srec_write_record (bfd *abfd,
		   unsigned int type,
		   bfd_vma address,
		   const bfd_byte *data,
		   const bfd_byte *end)
{
  char buffer[2 * MAXCHUNK + 6];
  unsigned int check_sum = 0;
  const bfd_byte *src = data;
  char *dst = buffer;
  char *length;
  bfd_size_type wrlen;

  *dst++ = 'S';
  *dst++ = '0' + type;

  length = dst;
  dst += 2;			/* Leave room for dst.  */

  switch (type)
    {
    case 3:
    case 7:
      TOHEX (dst, (address >> 24), check_sum);
      dst += 2;
    case 8:
    case 2:
      TOHEX (dst, (address >> 16), check_sum);
      dst += 2;
    case 9:
    case 1:
    case 0:
      TOHEX (dst, (address >> 8), check_sum);
      dst += 2;
      TOHEX (dst, (address), check_sum);
      dst += 2;
      break;

    }
  for (src = data; src < end; src++)
    {
      TOHEX (dst, *src, check_sum);
      dst += 2;
    }

  /* Fill in the length.  */
  TOHEX (length, (dst - length) / 2, check_sum);
  check_sum &= 0xff;
  check_sum = 255 - check_sum;
  TOHEX (dst, check_sum, check_sum);
  dst += 2;

  *dst++ = '\r';
  *dst++ = '\n';
  wrlen = dst - buffer;

  return bfd_bwrite ((void *) buffer, wrlen, abfd) == wrlen;
}