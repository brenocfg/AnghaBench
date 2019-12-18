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
struct reloc_entry {int reloc; } ;

/* Variables and functions */
 int BFD_RELOC_UNUSED ; 
 int /*<<< orphan*/  arm_reloc_hsh ; 
 struct reloc_entry* hash_find_n (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
parse_reloc (char **str)
{
  struct reloc_entry *r;
  char *p, *q;

  if (**str != '(')
    return BFD_RELOC_UNUSED;

  p = *str + 1;
  q = p;

  while (*q && *q != ')' && *q != ',')
    q++;
  if (*q != ')')
    return -1;

  if ((r = hash_find_n (arm_reloc_hsh, p, q - p)) == NULL)
    return -1;

  *str = q + 1;
  return r->reloc;
}