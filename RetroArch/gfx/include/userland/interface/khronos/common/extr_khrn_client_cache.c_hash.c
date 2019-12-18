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
typedef  int uint32_t ;

/* Variables and functions */
 int khrn_hashlittle (void const*,int,int /*<<< orphan*/ ) ; 
 int khrn_hashword (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t hash(const void *data, int len, int sig)
{
   int hash;

//   if (len > 256)     // TODO: turn this on later
//      len = 256;

   if (!((size_t)data & 3) && !(len & 3))
      hash = khrn_hashword((uint32_t *)data, len >> 2, 0);
   else
      hash = khrn_hashlittle(data, len, 0);

   return (hash & ~0xf) | sig;
}