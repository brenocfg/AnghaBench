#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct rpng_process {scalar_t__ avail_in; scalar_t__ avail_out; int inflate_initialized; int /*<<< orphan*/  palette; scalar_t__ restore_buf_size; scalar_t__ adam7_restore_buf_size; int /*<<< orphan*/ * stream; TYPE_1__* stream_backend; int /*<<< orphan*/  total_out; } ;
struct TYPE_7__ {int width; int height; int interlace; } ;
struct TYPE_6__ {TYPE_4__ ihdr; int /*<<< orphan*/  palette; scalar_t__ process; } ;
typedef  TYPE_2__ rpng_t ;
typedef  enum trans_stream_error { ____Placeholder_trans_stream_error } trans_stream_error ;
struct TYPE_5__ {int (* trans ) (int /*<<< orphan*/ *,int,scalar_t__*,scalar_t__*,int*) ;int /*<<< orphan*/  (* stream_free ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int TRANS_STREAM_ERROR_BUFFER_FULL ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ memalign (int,int) ; 
 int png_reverse_filter_init (TYPE_4__*,struct rpng_process*) ; 
 int stub1 (int /*<<< orphan*/ *,int,scalar_t__*,scalar_t__*,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rpng_load_image_argb_process_inflate_init(rpng_t *rpng, uint32_t **data)
{
   bool zstatus;
   enum trans_stream_error terror;
   uint32_t rd, wn;
   struct rpng_process *process = (struct rpng_process*)rpng->process;
   bool to_continue        = (process->avail_in > 0
         && process->avail_out > 0);

   if (!to_continue)
      goto end;

   zstatus = process->stream_backend->trans(process->stream, false, &rd, &wn, &terror);

   if (!zstatus && terror != TRANS_STREAM_ERROR_BUFFER_FULL)
      goto error;

   process->avail_in -= rd;
   process->avail_out -= wn;
   process->total_out += wn;

   if (terror)
      return 0;

end:
   process->stream_backend->stream_free(process->stream);
   process->stream = NULL;

#ifdef GEKKO
   /* we often use these in textures, make sure they're 32-byte aligned */
   *data = (uint32_t*)memalign(32, rpng->ihdr.width *
         rpng->ihdr.height * sizeof(uint32_t));
#else
   *data = (uint32_t*)malloc(rpng->ihdr.width *
         rpng->ihdr.height * sizeof(uint32_t));
#endif
   if (!*data)
      goto false_end;

   process->adam7_restore_buf_size = 0;
   process->restore_buf_size       = 0;
   process->palette                = rpng->palette;

   if (rpng->ihdr.interlace != 1)
      if (png_reverse_filter_init(&rpng->ihdr, process) == -1)
         goto false_end;

   process->inflate_initialized = true;
   return 1;

error:
false_end:
   process->inflate_initialized = false;
   return -1;
}