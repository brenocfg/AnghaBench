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
typedef  enum tag_types { ____Placeholder_tag_types } tag_types ;

/* Variables and functions */
#define  class_type 132 
#define  enum_type 131 
 int /*<<< orphan*/  gcc_unreachable () ; 
#define  record_type 130 
#define  typename_type 129 
#define  union_type 128 

__attribute__((used)) static const char *
tag_name (enum tag_types code)
{
  switch (code)
    {
    case record_type:
      return "struct";
    case class_type:
      return "class";
    case union_type:
      return "union";
    case enum_type:
      return "enum";
    case typename_type:
      return "typename";
    default:
      gcc_unreachable ();
    }
}