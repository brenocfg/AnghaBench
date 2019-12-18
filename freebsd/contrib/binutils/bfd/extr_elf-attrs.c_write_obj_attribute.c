#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; int i; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ obj_attribute ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 scalar_t__ is_default_attr (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * write_uleb128 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bfd_byte *
write_obj_attribute (bfd_byte *p, int tag, obj_attribute *attr)
{
  /* Suppress default entries.  */
  if (is_default_attr (attr))
    return p;

  p = write_uleb128 (p, tag);
  if (attr->type & 1)
    p = write_uleb128 (p, attr->i);
  if (attr->type & 2)
    {
      int len;

      len = strlen (attr->s) + 1;
      memcpy (p, attr->s, len);
      p += len;
    }

  return p;
}