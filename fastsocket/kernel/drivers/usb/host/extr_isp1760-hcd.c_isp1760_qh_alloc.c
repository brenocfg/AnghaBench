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
struct isp1760_qh {struct isp1760_hcd* priv; int /*<<< orphan*/  qtd_list; } ;
struct isp1760_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct isp1760_qh* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qh_cachep ; 

__attribute__((used)) static struct isp1760_qh *isp1760_qh_alloc(struct isp1760_hcd *priv,
		gfp_t flags)
{
	struct isp1760_qh *qh;

	qh = kmem_cache_zalloc(qh_cachep, flags);
	if (!qh)
		return qh;

	INIT_LIST_HEAD(&qh->qtd_list);
	qh->priv = priv;
	return qh;
}