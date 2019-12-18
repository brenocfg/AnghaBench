#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_11__ {char* option; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_9__ {TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int,unsigned int) ; 
 unsigned int PEEK_BYTES (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int PEEK_U8 (TYPE_2__*) ; 
 int /*<<< orphan*/  SKIP_BYTES (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_NOT_FOUND ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  _SKIP_U8 (TYPE_2__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T read_yuv4mpeg2_option( VC_CONTAINER_T *ctx,
   unsigned int *bytes_left )
{
   VC_CONTAINER_MODULE_T *module = ctx->priv->module;
   unsigned int size, i;

   /* Start by skipping spaces */
   while (*bytes_left && PEEK_U8(ctx) == ' ')
      (*bytes_left)--, _SKIP_U8(ctx);

   size = PEEK_BYTES(ctx, module->option,
      MIN(sizeof(module->option), *bytes_left));

   /* The config option ends at next space or newline */
   for (i = 0; i < size; i++)
   {
      if (module->option[i] == ' ' || module->option[i] == 0x0a)
      {
         module->option[i] = 0;
         break;
      }
   }
   if (i == 0)
      return VC_CONTAINER_ERROR_NOT_FOUND;

   *bytes_left -= i;
   SKIP_BYTES(ctx, i);

   /* If option is too long, we just discard it */
   if (i == size)
   {
      while (*bytes_left && PEEK_U8(ctx) != ' ' && PEEK_U8(ctx) != 0x0a)
         (*bytes_left)--, _SKIP_U8(ctx);
      return VC_CONTAINER_ERROR_NOT_FOUND;
   }

   return VC_CONTAINER_SUCCESS;
}