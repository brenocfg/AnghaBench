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
struct coff_scope {int dummy; } ;

/* Variables and functions */
 scalar_t__ xcalloc (int,int) ; 

__attribute__((used)) static struct coff_scope *
empty_scope (void)
{
  struct coff_scope *l;
  l = (struct coff_scope *) (xcalloc (sizeof (struct coff_scope), 1));
  return l;
}