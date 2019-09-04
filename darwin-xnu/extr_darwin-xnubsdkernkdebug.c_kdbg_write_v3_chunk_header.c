#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vnode_t ;
typedef  int /*<<< orphan*/ * vfs_context_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  sub_tag; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ kd_chunk_header_v3 ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int KERN_SUCCESS ; 
 int RAW_file_offset ; 
 int /*<<< orphan*/  assert (int) ; 
 int copyout (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int kdbg_write_to_vnode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
kdbg_write_v3_chunk_header(user_addr_t buffer, uint32_t tag, uint32_t sub_tag, uint64_t length, vnode_t vp, vfs_context_t ctx)
{
	int ret = KERN_SUCCESS;
	kd_chunk_header_v3 header = {
		.tag = tag,
		.sub_tag = sub_tag,
		.length = length,
	};

	// Check that only one of them is valid
	assert(!buffer ^ !vp);
	assert((vp == NULL) || (ctx != NULL));

	// Write the 8-byte future_chunk_timestamp field in the payload
	if (buffer || vp) {
		if (vp) {
			ret = kdbg_write_to_vnode((caddr_t)&header, sizeof(kd_chunk_header_v3), vp, ctx, RAW_file_offset);
			if (ret) {
				goto write_error;
			}
			RAW_file_offset  += (sizeof(kd_chunk_header_v3));
		}
		else {
			ret = copyout(&header, buffer, sizeof(kd_chunk_header_v3));
			if (ret) {
				goto write_error;
			}
		}
	}
write_error:
	return ret;
}