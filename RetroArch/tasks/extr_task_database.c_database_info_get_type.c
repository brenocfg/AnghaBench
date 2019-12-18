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
typedef  enum database_type { ____Placeholder_database_type } database_type ;
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ database_info_handle_t ;

/* Variables and functions */
 int DATABASE_TYPE_NONE ; 

__attribute__((used)) static enum database_type database_info_get_type(
      database_info_handle_t *handle)
{
   if (!handle)
      return DATABASE_TYPE_NONE;
   return handle->type;
}