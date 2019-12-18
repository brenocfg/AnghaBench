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
struct kfifo {int dummy; } ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int __kfifo_put (struct kfifo*,void*,int) ; 

__attribute__((used)) static inline int cq_put(struct kfifo *kfifo, void *p)
{
	return __kfifo_put(kfifo, (void *)&p, sizeof(p));
}