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
struct using_direct {struct using_direct* next; void* outer; void* inner; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 
 void* savestring (char const*,unsigned int) ; 
 struct using_direct* xmalloc (int) ; 

__attribute__((used)) static struct using_direct *
cp_add_using (const char *name,
	      unsigned int inner_len,
	      unsigned int outer_len,
	      struct using_direct *next)
{
  struct using_direct *retval;

  gdb_assert (outer_len < inner_len);

  retval = xmalloc (sizeof (struct using_direct));
  retval->inner = savestring (name, inner_len);
  retval->outer = savestring (name, outer_len);
  retval->next = next;

  return retval;
}