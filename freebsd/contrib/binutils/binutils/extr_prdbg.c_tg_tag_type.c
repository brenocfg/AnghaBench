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
struct pr_handle {int dummy; } ;
typedef  enum debug_type_kind { ____Placeholder_debug_type_kind } debug_type_kind ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
#define  DEBUG_KIND_CLASS 132 
#define  DEBUG_KIND_ENUM 131 
#define  DEBUG_KIND_STRUCT 130 
#define  DEBUG_KIND_UNION 129 
#define  DEBUG_KIND_UNION_CLASS 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  append_type (struct pr_handle*,char const*) ; 
 int /*<<< orphan*/  push_type (struct pr_handle*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
tg_tag_type (void *p, const char *name, unsigned int id,
	     enum debug_type_kind kind)
{
  struct pr_handle *info = (struct pr_handle *) p;
  const char *t, *tag;
  char idbuf[20];

  switch (kind)
    {
    case DEBUG_KIND_STRUCT:
      t = "struct ";
      break;
    case DEBUG_KIND_UNION:
      t = "union ";
      break;
    case DEBUG_KIND_ENUM:
      t = "enum ";
      break;
    case DEBUG_KIND_CLASS:
      t = "class ";
      break;
    case DEBUG_KIND_UNION_CLASS:
      t = "union class ";
      break;
    default:
      abort ();
      return FALSE;
    }

  if (! push_type (info, t))
    return FALSE;
  if (name != NULL)
    tag = name;
  else
    {
      sprintf (idbuf, "%%anon%u", id);
      tag = idbuf;
    }

  if (! append_type (info, tag))
    return FALSE;

  return TRUE;
}