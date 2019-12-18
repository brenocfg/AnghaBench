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
struct pidmap {int dummy; } ;
struct pid_namespace {struct pidmap* pidmap; } ;

/* Variables and functions */
 int BITS_PER_PAGE ; 

__attribute__((used)) static inline int mk_pid(struct pid_namespace *pid_ns,
		struct pidmap *map, int off)
{
	return (map - pid_ns->pidmap)*BITS_PER_PAGE + off;
}