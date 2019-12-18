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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  nspace_type_t ;

/* Variables and functions */
 int NAMESPACE_HANDLER_EVENT_TYPE_MASK ; 
#define  NAMESPACE_HANDLER_NSPACE_EVENT 129 
#define  NAMESPACE_HANDLER_SNAPSHOT_EVENT 128 
 int /*<<< orphan*/  NSPACE_HANDLER_NSPACE ; 
 int /*<<< orphan*/  NSPACE_HANDLER_SNAPSHOT ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static inline nspace_type_t nspace_type_for_op(uint64_t op)
{
	switch(op & NAMESPACE_HANDLER_EVENT_TYPE_MASK) {
		case NAMESPACE_HANDLER_NSPACE_EVENT:
			return NSPACE_HANDLER_NSPACE;
		case NAMESPACE_HANDLER_SNAPSHOT_EVENT:
			return NSPACE_HANDLER_SNAPSHOT;
		default:
			printf("nspace_type_for_op: invalid op mask %llx\n", op & NAMESPACE_HANDLER_EVENT_TYPE_MASK);
			return NSPACE_HANDLER_NSPACE;
	}
}