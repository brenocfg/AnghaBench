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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int errno ; 
 int filestream_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  swap_if_little16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_if_little32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_if_little64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_uint(RFILE *fd, uint64_t *out, size_t size)
{
   uint64_t tmp;

   if (filestream_read(fd, &tmp, size) == -1)
      goto error;

   switch (size)
   {
      case 1:
         *out = *(uint8_t *)(&tmp);
         break;
      case 2:
         *out = swap_if_little16((uint16_t)tmp);
         break;
      case 4:
         *out = swap_if_little32((uint32_t)tmp);
         break;
      case 8:
         *out = swap_if_little64(tmp);
         break;
   }
   return 0;

error:
   return -errno;
}