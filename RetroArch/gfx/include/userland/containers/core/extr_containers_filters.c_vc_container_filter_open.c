#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;
struct TYPE_7__ {int /*<<< orphan*/ * container; int /*<<< orphan*/ * priv; } ;
typedef  TYPE_1__ VC_CONTAINER_FILTER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FILTER_PRIVATE_T ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_ERROR_NOT_FOUND ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vc_container_filter_load (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VC_CONTAINER_FILTER_T *vc_container_filter_open(VC_CONTAINER_FOURCC_T filter,
                                                VC_CONTAINER_FOURCC_T type,
                                                VC_CONTAINER_T *p_container,
   VC_CONTAINER_STATUS_T *p_status )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_ERROR_NOT_FOUND;
   VC_CONTAINER_FILTER_T *p_ctx = 0;
   VC_CONTAINER_FILTER_PRIVATE_T *priv = 0;

   /* Allocate our context before trying out the different filter modules */
   p_ctx = malloc(sizeof(*p_ctx) + sizeof(*priv));
   if(!p_ctx) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }
   memset(p_ctx, 0, sizeof(*p_ctx) + sizeof(*priv));
   p_ctx->priv = priv = (VC_CONTAINER_FILTER_PRIVATE_T *)&p_ctx[1];
   p_ctx->container = p_container;

   status = vc_container_filter_load(p_ctx, filter, type);
   if(status != VC_CONTAINER_SUCCESS) goto error;

 end:
   if(p_status) *p_status = status;
   return p_ctx;

 error:
   if(p_ctx) free(p_ctx);
   p_ctx = 0;
   goto end;
}