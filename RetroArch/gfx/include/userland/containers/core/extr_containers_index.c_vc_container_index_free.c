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
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_INDEX_T ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FAILED ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

VC_CONTAINER_STATUS_T vc_container_index_free( VC_CONTAINER_INDEX_T *index )
{
   if(index == NULL)
      return VC_CONTAINER_ERROR_FAILED;

   free(index);
   return VC_CONTAINER_SUCCESS;
}