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
struct macro_table {scalar_t__ bcache; } ;

/* Variables and functions */
 void const* bcache (void const*,int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 
 void* xmalloc (int) ; 

__attribute__((used)) static const void *
macro_bcache (struct macro_table *t, const void *addr, int len)
{
  if (t->bcache)
    return bcache (addr, len, t->bcache);
  else
    {
      void *copy = xmalloc (len);
      memcpy (copy, addr, len);
      return copy;
    }
}