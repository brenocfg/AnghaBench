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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  mpgv_startcode ;
typedef  int /*<<< orphan*/  h ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BYTESTREAM_T ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ bytestream_peek_at (int /*<<< orphan*/ *,size_t,int*,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mpgv_read_picture_header(VC_CONTAINER_BYTESTREAM_T *stream,
   size_t offset, unsigned int *type, unsigned int *temporal_ref)
{
   VC_CONTAINER_STATUS_T status;
   uint8_t h[2];

   status = bytestream_peek_at(stream, offset + sizeof(mpgv_startcode) + 1, h, sizeof(h));
   if(status != VC_CONTAINER_SUCCESS)
      return status;

   *temporal_ref = (h[0] << 2) | (h[1] >> 6);
   *type = (h[1] >> 3) & 0x7;
   return VC_CONTAINER_SUCCESS;
}