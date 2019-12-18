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
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_5__ {int len; int mgap; } ;
typedef  TYPE_1__ VC_CONTAINER_INDEX_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_INDEX_POS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

VC_CONTAINER_STATUS_T vc_container_index_create( VC_CONTAINER_INDEX_T **index, int length )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_ERROR_OUT_OF_MEMORY;
   VC_CONTAINER_INDEX_T *id = NULL;
   int len = 0;

   if(length < 16) length = 16;
   if(length > 4096) length = 4096;
   while((length >>= 1) != 0)
      len++;

   id = malloc(sizeof(VC_CONTAINER_INDEX_T) + (sizeof(VC_CONTAINER_INDEX_POS_T)<<len));
   if(id == NULL) { goto error; }

   memset(id, 0, sizeof(VC_CONTAINER_INDEX_T));

   id->len = id->mgap = len;

   *index = id;
   return VC_CONTAINER_SUCCESS;

 error:
   return status;
}