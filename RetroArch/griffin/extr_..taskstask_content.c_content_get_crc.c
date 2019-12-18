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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int) ; 
 scalar_t__ content_rom_crc ; 
 scalar_t__ file_crc32 (int /*<<< orphan*/ ,char const*) ; 
 int pending_content_rom_crc ; 
 scalar_t__ pending_content_rom_crc_path ; 

uint32_t content_get_crc(void)
{
   if (pending_content_rom_crc)
   {
      pending_content_rom_crc      = false;
      content_rom_crc              = file_crc32(0,
            (const char*)pending_content_rom_crc_path);
      RARCH_LOG("CRC32: 0x%x .\n", (unsigned)content_rom_crc);
   }
   return content_rom_crc;
}