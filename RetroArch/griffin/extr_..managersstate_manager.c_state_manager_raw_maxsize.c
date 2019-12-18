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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int UINT16_MAX ; 

__attribute__((used)) static size_t state_manager_raw_maxsize(size_t uncomp)
{
   /* bytes covered by a compressed block */
   const int maxcblkcover = UINT16_MAX * sizeof(uint16_t);
   /* uncompressed size, rounded to 16 bits */
   size_t uncomp16        = (uncomp + sizeof(uint16_t) - 1) & -sizeof(uint16_t);
   /* number of blocks */
   size_t maxcblks        = (uncomp + maxcblkcover - 1) / maxcblkcover;
   return uncomp16 + maxcblks * sizeof(uint16_t) * 2 /* two u16 overhead per block */ + sizeof(uint16_t) *
      3; /* three u16 to end it */
}