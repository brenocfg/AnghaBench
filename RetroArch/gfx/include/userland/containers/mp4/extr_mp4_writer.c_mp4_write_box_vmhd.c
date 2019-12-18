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
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WRITE_U16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U24 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  WRITE_U8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_write_box_vmhd( VC_CONTAINER_T *p_ctx )
{
   WRITE_U8(p_ctx,  0, "version");
   WRITE_U24(p_ctx, 1, "flags");

   WRITE_U16(p_ctx,  0, "graphicsmode");
   WRITE_U16(p_ctx,  0, "opcolor");
   WRITE_U16(p_ctx,  0, "opcolor");
   WRITE_U16(p_ctx,  0, "opcolor");

   return STREAM_STATUS(p_ctx);
}