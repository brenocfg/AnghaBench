#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int NINFO ; 
 TYPE_1__* chunk_info ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
findb(const png_byte *name)
{
   int i = NINFO;
   while (--i >= 0)
   {
      if (memcmp(chunk_info[i].name, name, 4) == 0)
         break;
   }

   return i;
}