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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 scalar_t__ ASF_READ_U16 (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_STRING (int /*<<< orphan*/ *,scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  CHECK_POINT (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CORRUPTED ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_read_object_content_description( VC_CONTAINER_T *p_ctx, int64_t size )
{
   uint16_t t_length, a_length, c_length, d_length, r_length;

   t_length = ASF_READ_U16(p_ctx, size, "Title Length");
   a_length = ASF_READ_U16(p_ctx, size, "Author Length");
   c_length = ASF_READ_U16(p_ctx, size, "Copyright Length");
   d_length = ASF_READ_U16(p_ctx, size, "Description Length");
   r_length = ASF_READ_U16(p_ctx, size, "Rating Length");

   CHECK_POINT(p_ctx, size);

   if(size < t_length) return VC_CONTAINER_ERROR_CORRUPTED;
   ASF_SKIP_STRING(p_ctx, size, t_length, "Title");
   if(size < a_length) return VC_CONTAINER_ERROR_CORRUPTED;
   ASF_SKIP_STRING(p_ctx, size, a_length, "Author");
   if(size < c_length) return VC_CONTAINER_ERROR_CORRUPTED;
   ASF_SKIP_STRING(p_ctx, size, c_length, "Copyright");
   if(size < d_length) return VC_CONTAINER_ERROR_CORRUPTED;
   ASF_SKIP_STRING(p_ctx, size, d_length, "Description");
   if(size < r_length) return VC_CONTAINER_ERROR_CORRUPTED;
   ASF_SKIP_STRING(p_ctx, size, r_length, "Rating");

   return STREAM_STATUS(p_ctx);
}