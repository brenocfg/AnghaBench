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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct trans_stream_backend {int (* trans ) (void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ;int /*<<< orphan*/  (* stream_free ) (void*) ;int /*<<< orphan*/  (* set_out ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_in ) (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;void* (* stream_new ) () ;} ;
typedef  enum trans_stream_error { ____Placeholder_trans_stream_error } trans_stream_error ;

/* Variables and functions */
 int TRANS_STREAM_ERROR_ALLOCATION_FAILURE ; 
 void* stub1 () ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub4 (void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  stub5 (void*) ; 

bool trans_stream_trans_full(
    struct trans_stream_backend *backend, void **data,
    const uint8_t *in, uint32_t in_size,
    uint8_t *out, uint32_t out_size,
    enum trans_stream_error *error)
{
   void *rdata;
   bool ret;
   uint32_t rd, wn;

   if (data && *data)
   {
      rdata = *data;
   }
   else
   {
      rdata = backend->stream_new();
      if (!rdata)
      {
         if (error)
            *error = TRANS_STREAM_ERROR_ALLOCATION_FAILURE;
         return false;
      }
   }

   backend->set_in(rdata, in, in_size);
   backend->set_out(rdata, out, out_size);
   ret = backend->trans(rdata, true, &rd, &wn, error);

   if (data)
      *data = rdata;
   else
      backend->stream_free(rdata);

   return ret;
}