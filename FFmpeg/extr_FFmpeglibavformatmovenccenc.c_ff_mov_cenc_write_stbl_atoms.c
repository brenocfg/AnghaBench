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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  MOVMuxCencContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  mov_cenc_write_saio_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mov_cenc_write_saiz_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_cenc_write_senc_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ff_mov_cenc_write_stbl_atoms(MOVMuxCencContext* ctx, AVIOContext *pb)
{
    int64_t auxiliary_info_offset;

    mov_cenc_write_senc_tag(ctx, pb, &auxiliary_info_offset);
    mov_cenc_write_saio_tag(pb, auxiliary_info_offset);
    mov_cenc_write_saiz_tag(ctx, pb);
}