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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  intfstream_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  encoding_crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ intfstream_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int intfstream_get_crc(intfstream_t *fd, uint32_t *crc)
{
   int64_t read = 0;
   uint32_t acc = 0;
   uint8_t buffer[4096];

   while ((read = intfstream_read(fd, buffer, sizeof(buffer))) > 0)
      acc = encoding_crc32(acc, buffer, (size_t)read);

   if (read < 0)
      return 0;

   *crc = acc;

   return 1;
}