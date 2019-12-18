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
struct netfs_lock {void* type; void* size; void* ino; void* start; } ;

/* Variables and functions */
 void* __cpu_to_be32 (void*) ; 
 void* __cpu_to_be64 (void*) ; 

__attribute__((used)) static inline void netfs_convert_lock(struct netfs_lock *lock)
{
	lock->start = __cpu_to_be64(lock->start);
	lock->ino = __cpu_to_be64(lock->ino);
	lock->size = __cpu_to_be32(lock->size);
	lock->type = __cpu_to_be32(lock->type);
}