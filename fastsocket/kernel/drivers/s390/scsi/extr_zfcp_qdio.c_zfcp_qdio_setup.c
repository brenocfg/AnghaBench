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
struct zfcp_qdio {int /*<<< orphan*/  stat_lock; int /*<<< orphan*/  req_q_lock; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {struct zfcp_qdio* qdio; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct zfcp_qdio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ zfcp_qdio_allocate (struct zfcp_qdio*) ; 
 int /*<<< orphan*/  zfcp_qdio_destroy (struct zfcp_qdio*) ; 

int zfcp_qdio_setup(struct zfcp_adapter *adapter)
{
	struct zfcp_qdio *qdio;

	qdio = kzalloc(sizeof(struct zfcp_qdio), GFP_KERNEL);
	if (!qdio)
		return -ENOMEM;

	qdio->adapter = adapter;

	if (zfcp_qdio_allocate(qdio)) {
		zfcp_qdio_destroy(qdio);
		return -ENOMEM;
	}

	spin_lock_init(&qdio->req_q_lock);
	spin_lock_init(&qdio->stat_lock);

	adapter->qdio = qdio;
	return 0;
}