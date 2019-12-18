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

/* Variables and functions */
 int /*<<< orphan*/  COMPLETE_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const_type_info_type_node ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  flag_rtti ; 

__attribute__((used)) static bool
typeid_ok_p (void)
{
  if (! flag_rtti)
    {
      error ("cannot use typeid with -fno-rtti");
      return false;
    }

  if (!COMPLETE_TYPE_P (const_type_info_type_node))
    {
      error ("must #include <typeinfo> before using typeid");
      return false;
    }

  return true;
}