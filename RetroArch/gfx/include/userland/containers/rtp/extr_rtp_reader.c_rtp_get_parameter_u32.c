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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_T ;
struct TYPE_3__ {char const* name; char* value; } ;
typedef  TYPE_1__ PARAMETER_T ;

/* Variables and functions */
 int /*<<< orphan*/  strtoul (char*,char**,int) ; 
 scalar_t__ vc_containers_list_find_entry (int /*<<< orphan*/  const*,TYPE_1__*) ; 

bool rtp_get_parameter_u32(const VC_CONTAINERS_LIST_T *param_list,
      const char *name,
      uint32_t *value)
{
   PARAMETER_T param;

   param.name = name;
   if (vc_containers_list_find_entry(param_list, &param) && param.value)
   {
      char *end;

      *value = strtoul(param.value, &end, 10);
      return (end != param.value) && (*end == '\0');
   }

   return false;
}