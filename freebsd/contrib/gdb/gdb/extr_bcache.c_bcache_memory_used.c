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
struct bcache {int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 int obstack_memory_used (int /*<<< orphan*/ *) ; 

int
bcache_memory_used (struct bcache *bcache)
{
  return obstack_memory_used (&bcache->cache);
}