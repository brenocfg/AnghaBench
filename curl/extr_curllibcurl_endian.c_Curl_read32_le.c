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

/* Variables and functions */

unsigned int Curl_read32_le(const unsigned char *buf)
{
  return ((unsigned int)buf[0]) | ((unsigned int)buf[1] << 8) |
         ((unsigned int)buf[2] << 16) | ((unsigned int)buf[3] << 24);
}