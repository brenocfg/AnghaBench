#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s; } ;
struct sevenzip_context_t {scalar_t__ output; TYPE_2__* handle; int /*<<< orphan*/  allocTempImp; int /*<<< orphan*/  allocImp; int /*<<< orphan*/  block_index; int /*<<< orphan*/  index; TYPE_1__ lookStream; int /*<<< orphan*/  db; } ;
struct TYPE_4__ {scalar_t__ data; } ;
typedef  scalar_t__ SRes ;

/* Variables and functions */
 scalar_t__ SZ_ERROR_FAIL ; 
 scalar_t__ SZ_OK ; 
 scalar_t__ SzArEx_Extract (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,size_t*,size_t*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sevenzip_stream_decompress_data_to_file_iterate(void *data)
{
   struct sevenzip_context_t *sevenzip_context =
         (struct sevenzip_context_t*)data;

   SRes res                = SZ_ERROR_FAIL;
   size_t output_size      = 0;
   size_t offset           = 0;
   size_t outSizeProcessed = 0;

   res = SzArEx_Extract(&sevenzip_context->db,
         &sevenzip_context->lookStream.s, sevenzip_context->index,
         &sevenzip_context->block_index, &sevenzip_context->output,
         &output_size, &offset, &outSizeProcessed,
         &sevenzip_context->allocImp, &sevenzip_context->allocTempImp);

   if (res != SZ_OK)
      return 0;

   if (sevenzip_context->handle)
      sevenzip_context->handle->data = sevenzip_context->output + offset;

   return 1;
}