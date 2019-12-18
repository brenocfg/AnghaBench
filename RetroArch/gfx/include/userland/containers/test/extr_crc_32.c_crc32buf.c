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
typedef  int uint32_t ;

/* Variables and functions */
 int UPDC32 (int /*<<< orphan*/  const,int) ; 

uint32_t crc32buf(const uint8_t *buf, size_t len)
{
      register uint32_t oldcrc32;

      oldcrc32 = 0xFFFFFFFF;

      for ( ; len; --len, ++buf)
      {
            oldcrc32 = UPDC32(*buf, oldcrc32);
      }

      return ~oldcrc32;
}