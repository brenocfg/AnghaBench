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
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int errno ; 
 int filestream_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  swap_if_little16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_if_little32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_if_little64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_int(RFILE *fd, int64_t *out, size_t size)
{
   uint8_t tmp8 = 0;
   uint16_t tmp16;
   uint32_t tmp32;
   uint64_t tmp64;

   if (filestream_read(fd, &tmp64, size) == -1)
      goto error;

   (void)tmp8;

   switch (size)
   {
      case 1:
         *out = *((int8_t *)(&tmp64));
         break;
      case 2:
         tmp16 = swap_if_little16((uint16_t)tmp64);
         *out = *((int16_t *)(&tmp16));
         break;
      case 4:
         tmp32 = swap_if_little32((uint32_t)tmp64);
         *out = *((int32_t *)(&tmp32));
         break;
      case 8:
         tmp64 = swap_if_little64(tmp64);
         *out = *((int64_t *)(&tmp64));
         break;
   }
   return 0;

error:
   return -errno;
}