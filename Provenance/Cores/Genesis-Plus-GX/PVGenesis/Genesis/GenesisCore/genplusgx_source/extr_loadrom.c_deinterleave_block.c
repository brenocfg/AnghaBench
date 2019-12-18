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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void deinterleave_block(uint8 * src)
{
  int i;
  uint8 block[0x4000];
  memcpy (block, src, 0x4000);
  for (i = 0; i < 0x2000; i += 1)
  {
    src[i * 2 + 0] = block[0x2000 + (i)];
    src[i * 2 + 1] = block[0x0000 + (i)];
  }
}