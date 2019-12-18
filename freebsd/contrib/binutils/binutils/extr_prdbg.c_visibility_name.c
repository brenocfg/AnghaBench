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
typedef  enum debug_visibility { ____Placeholder_debug_visibility } debug_visibility ;

/* Variables and functions */
#define  DEBUG_VISIBILITY_IGNORE 131 
#define  DEBUG_VISIBILITY_PRIVATE 130 
#define  DEBUG_VISIBILITY_PROTECTED 129 
#define  DEBUG_VISIBILITY_PUBLIC 128 
 char const* FALSE ; 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static const char *
visibility_name (enum debug_visibility visibility)
{
  const char *s;

  switch (visibility)
    {
    case DEBUG_VISIBILITY_PUBLIC:
      s = "public";
      break;
    case DEBUG_VISIBILITY_PRIVATE:
      s = "private";
      break;
    case DEBUG_VISIBILITY_PROTECTED:
      s = "protected";
      break;
    case DEBUG_VISIBILITY_IGNORE:
      s = "/* ignore */";
      break;
    default:
      abort ();
      return FALSE;
    }
  return s;
}