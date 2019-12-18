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
struct nfs_pageio_descriptor {int /*<<< orphan*/  pg_recoalesce; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_do_recoalesce (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_pageio_doio (struct nfs_pageio_descriptor*) ; 

void nfs_pageio_complete(struct nfs_pageio_descriptor *desc)
{
	for (;;) {
		nfs_pageio_doio(desc);
		if (!desc->pg_recoalesce)
			break;
		if (!nfs_do_recoalesce(desc))
			break;
	}
}