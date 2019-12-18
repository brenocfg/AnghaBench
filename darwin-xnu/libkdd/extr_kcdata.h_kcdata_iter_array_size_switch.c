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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct thread_delta_snapshot_v2 {int dummy; } ;
struct stack_snapshot_frame64 {int dummy; } ;
struct stack_snapshot_frame32 {int dummy; } ;
struct dyld_uuid_info_64 {int dummy; } ;
struct dyld_uuid_info_32 {int dummy; } ;
typedef  int /*<<< orphan*/  kcdata_iter_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
#define  KCDATA_TYPE_LIBRARY_LOADINFO 136 
#define  KCDATA_TYPE_LIBRARY_LOADINFO64 135 
#define  STACKSHOT_KCTYPE_DONATING_PIDS 134 
#define  STACKSHOT_KCTYPE_KERN_STACKFRAME 133 
#define  STACKSHOT_KCTYPE_KERN_STACKFRAME64 132 
#define  STACKSHOT_KCTYPE_THREAD_DELTA_SNAPSHOT 131 
#define  STACKSHOT_KCTYPE_USER_STACKFRAME 130 
#define  STACKSHOT_KCTYPE_USER_STACKFRAME64 129 
#define  TASK_CRASHINFO_CRASHED_THREADID 128 
 int kcdata_iter_array_elem_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
uint32_t
kcdata_iter_array_size_switch(kcdata_iter_t iter) {
	switch(kcdata_iter_array_elem_type(iter)) {
	case KCDATA_TYPE_LIBRARY_LOADINFO:
		return sizeof(struct dyld_uuid_info_32);
	case KCDATA_TYPE_LIBRARY_LOADINFO64:
		return sizeof(struct dyld_uuid_info_64);
	case STACKSHOT_KCTYPE_KERN_STACKFRAME:
	case STACKSHOT_KCTYPE_USER_STACKFRAME:
		return sizeof(struct stack_snapshot_frame32);
	case STACKSHOT_KCTYPE_KERN_STACKFRAME64:
	case STACKSHOT_KCTYPE_USER_STACKFRAME64:
		return sizeof(struct stack_snapshot_frame64);
	case STACKSHOT_KCTYPE_DONATING_PIDS:
		return sizeof(int32_t);
	case STACKSHOT_KCTYPE_THREAD_DELTA_SNAPSHOT:
		return sizeof(struct thread_delta_snapshot_v2);
    // This one is only here to make some unit tests work. It should be OK to
    // remove.
	case TASK_CRASHINFO_CRASHED_THREADID:
		return sizeof(uint64_t);
	default:
		return 0;
	}
}