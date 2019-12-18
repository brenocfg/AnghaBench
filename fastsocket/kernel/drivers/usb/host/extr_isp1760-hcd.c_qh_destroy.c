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
struct isp1760_qh {int /*<<< orphan*/  qtd_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct isp1760_qh*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qh_cachep ; 

__attribute__((used)) static void qh_destroy(struct isp1760_qh *qh)
{
	BUG_ON(!list_empty(&qh->qtd_list));
	kmem_cache_free(qh_cachep, qh);
}