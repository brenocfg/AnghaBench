#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * dir; } ;
struct TYPE_4__ {TYPE_1__ pipefs; } ;
struct cache_detail {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_remove_cache_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunrpc_destroy_cache_detail (struct cache_detail*) ; 

void sunrpc_cache_unregister_pipefs(struct cache_detail *cd)
{
	rpc_remove_cache_dir(cd->u.pipefs.dir);
	cd->u.pipefs.dir = NULL;
	sunrpc_destroy_cache_detail(cd);
}