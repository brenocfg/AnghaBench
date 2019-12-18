#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct audit_context {int sockaddr_len; void* sockaddr; scalar_t__ dummy; } ;
struct TYPE_2__ {struct audit_context* audit_context; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* current ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

int audit_sockaddr(int len, void *a)
{
	struct audit_context *context = current->audit_context;

	if (likely(!context || context->dummy))
		return 0;

	if (!context->sockaddr) {
		void *p = kmalloc(sizeof(struct sockaddr_storage), GFP_KERNEL);
		if (!p)
			return -ENOMEM;
		context->sockaddr = p;
	}

	context->sockaddr_len = len;
	memcpy(context->sockaddr, a, len);
	return 0;
}