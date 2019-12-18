#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum debug_type_kind { ____Placeholder_debug_type_kind } debug_type_kind ;
typedef  TYPE_1__* debug_type ;
struct TYPE_5__ {int kind; } ;

/* Variables and functions */
 int DEBUG_KIND_ILLEGAL ; 
 TYPE_1__* debug_get_real_type (void*,TYPE_1__*,int /*<<< orphan*/ *) ; 

enum debug_type_kind
debug_get_type_kind (void *handle, debug_type type)
{
  if (type == NULL)
    return DEBUG_KIND_ILLEGAL;
  type = debug_get_real_type (handle, type, NULL);
  if (type == NULL)
    return DEBUG_KIND_ILLEGAL;
  return type->kind;
}