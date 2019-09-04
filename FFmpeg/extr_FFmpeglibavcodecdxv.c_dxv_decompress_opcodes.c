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
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_peek_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 
 int fill_ltable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int get_opcodes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int dxv_decompress_opcodes(GetByteContext *gb, void *dstp, size_t op_size)
{
    int pos = bytestream2_tell(gb);
    int flag = bytestream2_peek_byte(gb);

    if ((flag & 3) == 0) {
        bytestream2_skip(gb, 1);
        bytestream2_get_buffer(gb, dstp, op_size);
    } else if ((flag & 3) == 1) {
        bytestream2_skip(gb, 1);
        memset(dstp, bytestream2_get_byte(gb), op_size);
    } else {
        uint32_t table[256];
        int ret, elements = 0;

        ret = fill_ltable(gb, table, &elements);
        if (ret < 0)
            return ret;
        ret = get_opcodes(gb, table, dstp, op_size, elements);
        if (ret < 0)
            return ret;
    }
    return bytestream2_tell(gb) - pos;
}