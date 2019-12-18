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
struct alloc_zone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  new_ggc_zone_1 (struct alloc_zone*,char const*) ; 
 struct alloc_zone* xcalloc (int,int) ; 

struct alloc_zone *
new_ggc_zone (const char * name)
{
  struct alloc_zone *new_zone = xcalloc (1, sizeof (struct alloc_zone));
  new_ggc_zone_1 (new_zone, name);
  return new_zone;
}