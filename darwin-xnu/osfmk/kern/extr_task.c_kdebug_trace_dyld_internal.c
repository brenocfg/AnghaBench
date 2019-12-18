#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int fid_objno; int fid_generation; } ;
struct TYPE_3__ {int* val; } ;
struct dyld_kernel_image_info {int load_addr; TYPE_2__ fsobjid; TYPE_1__ fsid; int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DYLD ; 
 int /*<<< orphan*/  DBG_DYLD_UUID ; 
 int /*<<< orphan*/  KDBG_EVENTID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_assert (int) ; 

__attribute__((used)) static void
kdebug_trace_dyld_internal(uint32_t base_code,
	struct dyld_kernel_image_info *info)
{
	static_assert(sizeof(info->uuid) >= 16);

#if defined(__LP64__)
	uint64_t *uuid = (uint64_t *)&(info->uuid);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
		KDBG_EVENTID(DBG_DYLD, DBG_DYLD_UUID, base_code), uuid[0],
		uuid[1], info->load_addr,
		(uint64_t)info->fsid.val[0] | ((uint64_t)info->fsid.val[1] << 32),
		0);
	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
		KDBG_EVENTID(DBG_DYLD, DBG_DYLD_UUID, base_code + 1),
		(uint64_t)info->fsobjid.fid_objno |
		((uint64_t)info->fsobjid.fid_generation << 32),
		0, 0, 0, 0);
#else /* defined(__LP64__) */
	uint32_t *uuid = (uint32_t *)&(info->uuid);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
		KDBG_EVENTID(DBG_DYLD, DBG_DYLD_UUID, base_code + 2), uuid[0],
		uuid[1], uuid[2], uuid[3], 0);
	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
		KDBG_EVENTID(DBG_DYLD, DBG_DYLD_UUID, base_code + 3),
		(uint32_t)info->load_addr, info->fsid.val[0], info->fsid.val[1],
		info->fsobjid.fid_objno, 0);
	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
		KDBG_EVENTID(DBG_DYLD, DBG_DYLD_UUID, base_code + 4),
		info->fsobjid.fid_generation, 0, 0, 0, 0);
#endif /* !defined(__LP64__) */
}