#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_10__ {char* line; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_8__ {TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (TYPE_2__*,char*) ; 
 unsigned int PEEK_BYTES (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  SKIP_BYTES (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CORRUPTED ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_EOS ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T simple_read_line( VC_CONTAINER_T *ctx )
{
   VC_CONTAINER_MODULE_T *module = ctx->priv->module;
   unsigned int i, bytes = PEEK_BYTES(ctx, module->line, sizeof(module->line)-1);

   if (!bytes)
      return VC_CONTAINER_ERROR_EOS;

   /* Find new-line marker */
   for (i = 0; i < bytes; i++)
      if (module->line[i] == '\n')
         break;

   /* Bail out if line is bigger than the maximum allowed */
   if (i == sizeof(module->line)-1)
   {
      LOG_ERROR(ctx, "line too big");
      return VC_CONTAINER_ERROR_CORRUPTED;
   }

   if (i < bytes)
   {
      module->line[i++] = 0;
      if (i < bytes && module->line[i] == '\r')
         i++;
   }
   module->line[i] = 0; /* Make sure the line is null terminated */

   SKIP_BYTES(ctx, i);
   return VC_CONTAINER_SUCCESS;
}