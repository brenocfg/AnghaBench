#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ output_handle; scalar_t__ output; scalar_t__ input_handle; scalar_t__ input; } ;
struct TYPE_11__ {scalar_t__ type; } ;
typedef  TYPE_1__ BRCMJPEG_T ;
typedef  int /*<<< orphan*/  BRCMJPEG_STATUS_T ;
typedef  TYPE_2__ BRCMJPEG_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMJPEG_ERROR_REQUEST ; 
 scalar_t__ BRCMJPEG_TYPE_ENCODER ; 
 int /*<<< orphan*/  LOCK_PROCESS (TYPE_1__*) ; 
 int /*<<< orphan*/  LOG_ERROR (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  UNLOCK_PROCESS (TYPE_1__*) ; 
 int /*<<< orphan*/  brcmjpeg_decode (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  brcmjpeg_encode (TYPE_1__*,TYPE_2__*) ; 

BRCMJPEG_STATUS_T brcmjpeg_process(BRCMJPEG_T *ctx, BRCMJPEG_REQUEST_T *req)
{
   BRCMJPEG_STATUS_T status;

   /* Sanity check */
   if ((req->input && req->input_handle) ||
       (req->output && req->output_handle))
   {
      LOG_ERROR("buffer pointer and handle both set (%p/%u %p/%u)",
            req->input, req->input_handle, req->output, req->output_handle);
      return BRCMJPEG_ERROR_REQUEST;
   }

   LOCK_PROCESS(ctx);
   if (ctx->type == BRCMJPEG_TYPE_ENCODER)
      status = brcmjpeg_encode(ctx, req);
   else
      status = brcmjpeg_decode(ctx, req);
   UNLOCK_PROCESS(ctx);

   return status;
}