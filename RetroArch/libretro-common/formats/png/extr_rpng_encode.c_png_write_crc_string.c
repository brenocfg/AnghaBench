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
typedef  int /*<<< orphan*/  crc_raw ;

/* Variables and functions */
 int /*<<< orphan*/  dword_write_be (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encoding_crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int intfstream_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool png_write_crc_string(intfstream_t *intf_s, const uint8_t *data, size_t size)
{
   uint8_t crc_raw[4] = {0};
   uint32_t crc       = encoding_crc32(0, data, size);

   dword_write_be(crc_raw, crc);
   return intfstream_write(intf_s, crc_raw, sizeof(crc_raw)) == sizeof(crc_raw);
}