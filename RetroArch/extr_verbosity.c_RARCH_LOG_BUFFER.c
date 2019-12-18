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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int verbosity_log_level ; 

void RARCH_LOG_BUFFER(uint8_t *data, size_t size)
{
   unsigned i, offset;
   int padding     = size % 16;
   uint8_t buf[16] = {0};

   if (verbosity_log_level > 1)
      return;

   RARCH_LOG("== %d-byte buffer ==================\n", (int)size);

   for (i = 0, offset = 0; i < size; i++)
   {
      buf[offset] = data[i];
      offset++;

      if (offset == 16)
      {
         offset = 0;
         RARCH_LOG("%02x%02x%02x%02x%02x%02x%02x%02x  %02x%02x%02x%02x%02x%02x%02x%02x\n",
            buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7],
            buf[8], buf[9], buf[10], buf[11], buf[12], buf[13], buf[14], buf[15]);
      }
   }

   if (padding)
   {
      for (i = padding; i < 16; i++)
         buf[i] = 0xff;
      RARCH_LOG("%02x%02x%02x%02x%02x%02x%02x%02x  %02x%02x%02x%02x%02x%02x%02x%02x\n",
         buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7],
         buf[8], buf[9], buf[10], buf[11], buf[12], buf[13], buf[14], buf[15]);
   }
   RARCH_LOG("==================================\n");
}