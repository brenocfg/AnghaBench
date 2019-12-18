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
struct nfs_pageio_descriptor {scalar_t__ pg_bsize; scalar_t__ pg_count; } ;
struct nfs_page {scalar_t__ wb_bytes; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 

bool nfs_generic_pg_test(struct nfs_pageio_descriptor *desc, struct nfs_page *prev, struct nfs_page *req)
{
	/*
	 * FIXME: ideally we should be able to coalesce all requests
	 * that are not block boundary aligned, but currently this
	 * is problematic for the case of bsize < PAGE_CACHE_SIZE,
	 * since nfs_flush_multi and nfs_pagein_multi assume you
	 * can have only one struct nfs_page.
	 */
	if (desc->pg_bsize < PAGE_SIZE)
		return 0;

	return desc->pg_count + req->wb_bytes <= desc->pg_bsize;
}