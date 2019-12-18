#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__ const* vtable; } ;
typedef  TYPE_1__ br_hash_compat_context ;
struct TYPE_8__ {int /*<<< orphan*/  (* out ) (TYPE_2__ const**,void*) ;int /*<<< orphan*/  (* update ) (TYPE_2__ const**,void const*,size_t) ;int /*<<< orphan*/  (* init ) (TYPE_2__ const**) ;} ;
typedef  TYPE_2__ br_hash_class ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__ const**) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__ const**,void const*,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__ const**,void*) ; 

__attribute__((used)) static void
hash_data(const br_hash_class *dig, void *dst, const void *src, size_t len)
{
	br_hash_compat_context hc;

	hc.vtable = dig;
	dig->init(&hc.vtable);
	dig->update(&hc.vtable, src, len);
	dig->out(&hc.vtable, dst);
}