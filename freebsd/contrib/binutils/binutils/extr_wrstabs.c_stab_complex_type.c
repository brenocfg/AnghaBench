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
struct stab_write_handle {long type_index; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sprintf (char*,char*,long,long,unsigned int) ; 
 int /*<<< orphan*/  stab_push_string (struct stab_write_handle*,char*,long,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static bfd_boolean
stab_complex_type (void *p, unsigned int size)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  char buf[50];
  long index;

  index = info->type_index;
  ++info->type_index;

  sprintf (buf, "%ld=r%ld;%u;0;", index, index, size);

  return stab_push_string (info, buf, index, TRUE, size * 2);
}