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
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_T ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ HTTP_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTION_NAME ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vc_containers_list_find_entry (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static bool io_http_check_persistent_connection(VC_CONTAINERS_LIST_T *header_list)
{
   HTTP_HEADER_T header;

   header.name = CONNECTION_NAME;
   if (header_list && vc_containers_list_find_entry(header_list, &header))
   {
      /* coverity[secure_coding] String is null-terminated */
      if (!strcasecmp(header.value, "close"))
         return false;
   }

   return true;
}