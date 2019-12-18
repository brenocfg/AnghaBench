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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int addrsize ; 
 int /*<<< orphan*/  checksum (int /*<<< orphan*/ *,unsigned char*,int,int) ; 
 int code ; 

__attribute__((used)) static void
writeINT (int n, unsigned char *ptr, int *idx, int size, FILE *file)
{
  int byte = *idx / 8;

  if (size == -2)
    size = addrsize;
  else if (size == -1)
    size = 0;

  if (byte > 240)
    {
      /* Lets write out that record and do another one.  */
      checksum (file, ptr, *idx, code | 0x1000);
      *idx = 16;
      byte = *idx / 8;
    }

  switch (size)
    {
    case 0:
      break;
    case 1:
      ptr[byte] = n;
      break;
    case 2:
      ptr[byte + 0] = n >> 8;
      ptr[byte + 1] = n;
      break;
    case 4:
      ptr[byte + 0] = n >> 24;
      ptr[byte + 1] = n >> 16;
      ptr[byte + 2] = n >> 8;
      ptr[byte + 3] = n >> 0;
      break;
    default:
      abort ();
    }
  *idx += size * 8;
}