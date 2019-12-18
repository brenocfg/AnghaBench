#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  supported_extensions_list; } ;
typedef  TYPE_1__ core_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  path_get_extension (char const*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int string_list_find_elem_prefix (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool core_info_does_support_file(
      const core_info_t *core, const char *path)
{
   if (!core || !core->supported_extensions_list)
      return false;
   if (string_is_empty(path))
      return false;

   return string_list_find_elem_prefix(
         core->supported_extensions_list, ".", path_get_extension(path));
}