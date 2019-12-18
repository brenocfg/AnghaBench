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
 int /*<<< orphan*/  VC_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  WRITE_FOURCC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  WRITE_U8 (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_write_box_vide_d263( VC_CONTAINER_T *p_ctx )
{
   WRITE_U32(p_ctx, 8 + 7, "size");
   WRITE_FOURCC(p_ctx, VC_FOURCC('d','2','6','3'), "type");
   WRITE_FOURCC(p_ctx, VC_FOURCC('B','R','C','M'), "vendor");
   WRITE_U8(p_ctx, 0, "version");
   WRITE_U8(p_ctx, 10, "level");
   WRITE_U8(p_ctx, 0, "profile");

   return STREAM_STATUS(p_ctx);
}