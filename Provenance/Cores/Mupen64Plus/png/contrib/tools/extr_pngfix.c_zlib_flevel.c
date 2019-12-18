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
struct zlib {int* header; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNREACHED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
zlib_flevel(struct zlib *zlib)
{
   switch (zlib->header[1] >> 6)
   {
      case 0:  return "supfast";
      case 1:  return "stdfast";
      case 2:  return "default";
      case 3:  return "maximum";
      default: assert(UNREACHED);
   }

   return "COMPILER BUG";
}