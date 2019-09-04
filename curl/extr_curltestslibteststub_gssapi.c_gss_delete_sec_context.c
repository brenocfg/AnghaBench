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
typedef  int /*<<< orphan*/ * gss_ctx_id_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_INVALID_CTX ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

OM_uint32 gss_delete_sec_context(OM_uint32 *min,
                                 gss_ctx_id_t *context_handle,
                                 gss_buffer_t output_token)
{
  (void)output_token;

  if(!min)
    return GSS_S_FAILURE;

  if(!context_handle) {
    *min = GSS_INVALID_CTX;
    return GSS_S_FAILURE;
  }

  free(*context_handle);
  *context_handle = NULL;
  *min = 0;

  return GSS_S_COMPLETE;
}