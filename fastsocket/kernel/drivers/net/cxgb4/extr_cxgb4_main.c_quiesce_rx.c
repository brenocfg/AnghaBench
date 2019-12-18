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
struct sge_rspq {int /*<<< orphan*/  napi; scalar_t__ handler; } ;
struct TYPE_2__ {struct sge_rspq** ingr_map; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sge_rspq**) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void quiesce_rx(struct adapter *adap)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(adap->sge.ingr_map); i++) {
		struct sge_rspq *q = adap->sge.ingr_map[i];

		if (q && q->handler)
			napi_disable(&q->napi);
	}
}