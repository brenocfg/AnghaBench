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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  intfstream_t ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int intfstream_write (int /*<<< orphan*/ *,char const*,int) ; 
 int png_write_crc_string (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static bool png_write_iend_string(intfstream_t* intf_s)
{
   const uint8_t data[] = {
      0, 0, 0, 0,
      'I', 'E', 'N', 'D',
   };

   if (intfstream_write(intf_s, data, sizeof(data)) != sizeof(data))
      return false;

   return png_write_crc_string(intf_s, data + sizeof(uint32_t),
         sizeof(data) - sizeof(uint32_t));
}