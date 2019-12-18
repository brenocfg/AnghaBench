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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASF_READ_U32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_read_object_content_encryption( VC_CONTAINER_T *p_ctx, int64_t size )
{
   uint32_t length;

   length = ASF_READ_U32(p_ctx, size, "Secret Data Length");
   ASF_SKIP_BYTES(p_ctx, size, length);

   length = ASF_READ_U32(p_ctx, size, "Protection Type Length");
   ASF_SKIP_BYTES(p_ctx, size, length);

   length = ASF_READ_U32(p_ctx, size, "Key ID Length");
   ASF_SKIP_BYTES(p_ctx, size, length);

   length = ASF_READ_U32(p_ctx, size, "License URL Length");
   ASF_SKIP_BYTES(p_ctx, size, length); /* null-terminated ASCII string */

   return STREAM_STATUS(p_ctx);
}