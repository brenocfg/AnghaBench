#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  al_elements; } ;
typedef  TYPE_1__ alist_t ;
struct TYPE_6__ {int (* aid_func ) (void*,void*,void*) ;void* aid_priv; } ;
typedef  TYPE_2__ alist_iter_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  alist_iter_cb ; 
 int hash_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

int
alist_iter(alist_t *alist, int (*func)(void *, void *, void *), void *private)
{
	alist_iter_data_t aid;

	aid.aid_func = func;
	aid.aid_priv = private;

	return (hash_iter(alist->al_elements, alist_iter_cb, &aid));
}