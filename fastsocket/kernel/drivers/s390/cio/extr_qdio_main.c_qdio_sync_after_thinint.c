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
struct qdio_q {int dummy; } ;

/* Variables and functions */
 scalar_t__ need_siga_sync_out_thinint (struct qdio_q*) ; 
 scalar_t__ need_siga_sync_thinint (struct qdio_q*) ; 
 scalar_t__ pci_out_supported (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_siga_sync_all (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_siga_sync_out (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_siga_sync_q (struct qdio_q*) ; 

__attribute__((used)) static inline void qdio_sync_after_thinint(struct qdio_q *q)
{
	if (pci_out_supported(q)) {
		if (need_siga_sync_thinint(q))
			qdio_siga_sync_all(q);
		else if (need_siga_sync_out_thinint(q))
			qdio_siga_sync_out(q);
	} else
		qdio_siga_sync_q(q);
}