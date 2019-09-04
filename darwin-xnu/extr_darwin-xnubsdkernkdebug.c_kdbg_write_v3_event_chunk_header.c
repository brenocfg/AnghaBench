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
typedef  int /*<<< orphan*/ * vnode_t ;
typedef  int /*<<< orphan*/ * vfs_context_t ;
typedef  int user_addr_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  kd_chunk_header_v3 ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int RAW_file_offset ; 
 int /*<<< orphan*/  V3_EVENT_DATA_VERSION ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ copyout (int*,int,int) ; 
 int kdbg_write_to_vnode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ kdbg_write_v3_chunk_header (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

user_addr_t
kdbg_write_v3_event_chunk_header(user_addr_t buffer, uint32_t tag, uint64_t length, vnode_t vp, vfs_context_t ctx)
{
        uint64_t future_chunk_timestamp = 0;
        length += sizeof(uint64_t);

        if (kdbg_write_v3_chunk_header(buffer, tag, V3_EVENT_DATA_VERSION, length, vp, ctx)) {
                return 0;
        }
        if (buffer) {
                buffer += sizeof(kd_chunk_header_v3);
        }

        // Check that only one of them is valid
        assert(!buffer ^ !vp);
        assert((vp == NULL) || (ctx != NULL));

        // Write the 8-byte future_chunk_timestamp field in the payload
        if (buffer || vp) {
                if (vp) {
                        int ret = kdbg_write_to_vnode((caddr_t)&future_chunk_timestamp, sizeof(uint64_t), vp, ctx, RAW_file_offset);
                        if (!ret) {
                                RAW_file_offset  += (sizeof(uint64_t));
                        }
                }
                else {
                        if (copyout(&future_chunk_timestamp, buffer, sizeof(uint64_t))) {
                                return 0;
                        }
                }
        }

        return (buffer + sizeof(uint64_t));
}