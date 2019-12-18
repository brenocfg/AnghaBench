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
struct nfs_pgio_header {int dummy; } ;
struct nfs_pageio_descriptor {scalar_t__ pg_bsize; } ;

/* Variables and functions */
 scalar_t__ PAGE_CACHE_SIZE ; 
 int nfs_flush_multi (struct nfs_pageio_descriptor*,struct nfs_pgio_header*) ; 
 int nfs_flush_one (struct nfs_pageio_descriptor*,struct nfs_pgio_header*) ; 

int nfs_generic_flush(struct nfs_pageio_descriptor *desc,
		      struct nfs_pgio_header *hdr)
{
	if (desc->pg_bsize < PAGE_CACHE_SIZE)
		return nfs_flush_multi(desc, hdr);
	return nfs_flush_one(desc, hdr);
}