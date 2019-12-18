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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  intfstream_t ;

/* Variables and functions */
 scalar_t__ intfstream_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int png_write_crc_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static bool png_write_idat_string(intfstream_t* intf_s, const uint8_t *data, size_t size)
{
   if (intfstream_write(intf_s, data, size) != (ssize_t)size)
      return false;

   return png_write_crc_string(intf_s, data + sizeof(uint32_t), size - sizeof(uint32_t));
}