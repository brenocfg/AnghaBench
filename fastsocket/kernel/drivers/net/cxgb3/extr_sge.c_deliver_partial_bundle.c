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
struct t3cdev {int /*<<< orphan*/  (* recv ) (struct t3cdev*,struct sk_buff**,int) ;} ;
struct sk_buff {int dummy; } ;
struct sge_rspq {int /*<<< orphan*/  offload_bundles; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct t3cdev*,struct sk_buff**,int) ; 

__attribute__((used)) static inline void deliver_partial_bundle(struct t3cdev *tdev,
					  struct sge_rspq *q,
					  struct sk_buff *skbs[], int n)
{
	if (n) {
		q->offload_bundles++;
		tdev->recv(tdev, skbs, n);
	}
}