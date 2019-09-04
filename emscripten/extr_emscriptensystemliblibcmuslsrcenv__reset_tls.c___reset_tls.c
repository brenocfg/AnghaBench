#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tls_module {int len; int size; int /*<<< orphan*/  image; struct tls_module* next; } ;
typedef  TYPE_1__* pthread_t ;
struct TYPE_5__ {struct tls_module* tls_head; } ;
struct TYPE_4__ {scalar_t__* dtv; } ;

/* Variables and functions */
 TYPE_1__* __pthread_self () ; 
 TYPE_2__ libc ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

void __reset_tls()
{
	pthread_t self = __pthread_self();
	struct tls_module *p;
	size_t i, n = (size_t)self->dtv[0];
	if (n) for (p=libc.tls_head, i=1; i<=n; i++, p=p->next) {
		if (!self->dtv[i]) continue;
		memcpy(self->dtv[i], p->image, p->len);
		memset((char *)self->dtv[i]+p->len, 0,
			p->size - p->len);
	}
}