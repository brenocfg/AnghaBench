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
struct TYPE_5__ {int /*<<< orphan*/ * component_list; int /*<<< orphan*/ * ilcs; int /*<<< orphan*/  component_lock; } ;
typedef  int /*<<< orphan*/  ILCS_SERVICE_T ;
typedef  TYPE_1__ ILCS_COMMON_T ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  vcos_free (TYPE_1__*) ; 
 TYPE_1__* vcos_malloc (int,char*) ; 
 scalar_t__ vcos_semaphore_create (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static ILCS_COMMON_T *vcilcs_common_init(ILCS_SERVICE_T *ilcs)
{
   ILCS_COMMON_T *st;

   st = vcos_malloc(sizeof(ILCS_COMMON_T), "ILCS_HOST_COMMON");
   if(!st)
      return NULL;

   if(vcos_semaphore_create(&st->component_lock, "ILCS", 1) != VCOS_SUCCESS)
   {
      vcos_free(st);
      return NULL;
   }

   st->ilcs = ilcs;
   st->component_list = NULL;
   return st;
}