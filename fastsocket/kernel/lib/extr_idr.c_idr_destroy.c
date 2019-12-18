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
struct idr_layer {int dummy; } ;
struct idr {scalar_t__ id_free_cnt; } ;

/* Variables and functions */
 struct idr_layer* get_from_free_list (struct idr*) ; 
 int /*<<< orphan*/  idr_layer_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct idr_layer*) ; 

void idr_destroy(struct idr *idp)
{
	while (idp->id_free_cnt) {
		struct idr_layer *p = get_from_free_list(idp);
		kmem_cache_free(idr_layer_cache, p);
	}
}