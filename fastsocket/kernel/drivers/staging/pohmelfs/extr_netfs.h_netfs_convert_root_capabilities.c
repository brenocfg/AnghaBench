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
struct netfs_root_capabilities {void* flags; void* avail; void* used; void* nr_files; } ;

/* Variables and functions */
 void* __cpu_to_be64 (void*) ; 

__attribute__((used)) static inline void netfs_convert_root_capabilities(struct netfs_root_capabilities *cap)
{
	cap->nr_files = __cpu_to_be64(cap->nr_files);
	cap->used = __cpu_to_be64(cap->used);
	cap->avail = __cpu_to_be64(cap->avail);
	cap->flags = __cpu_to_be64(cap->flags);
}