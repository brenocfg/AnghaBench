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
struct nfs4_filelayout_segment {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  filelayout_free_fh_array (struct nfs4_filelayout_segment*) ; 
 int /*<<< orphan*/  kfree (struct nfs4_filelayout_segment*) ; 

__attribute__((used)) static void
_filelayout_free_lseg(struct nfs4_filelayout_segment *fl)
{
	filelayout_free_fh_array(fl);
	kfree(fl);
}