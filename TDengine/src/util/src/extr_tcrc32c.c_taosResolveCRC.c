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
 int /*<<< orphan*/  SSE42 (int) ; 
 int /*<<< orphan*/  crc32c ; 
 int /*<<< orphan*/  crc32c_hw ; 
 int /*<<< orphan*/  crc32c_sf ; 

void taosResolveCRC() {
#ifndef _TD_ARM_
  int sse42;
  SSE42(sse42);
  crc32c = sse42 ? crc32c_hw : crc32c_sf;
#else
  crc32c = crc32c_sf;
#endif  
  /* return sse42 ? crc32c_hw(crci, bytes, len) : crc32c_sf(crci, bytes, len);
   */
}