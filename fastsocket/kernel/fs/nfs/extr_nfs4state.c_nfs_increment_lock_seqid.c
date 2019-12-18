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
struct nfs_seqid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_increment_seqid (int,struct nfs_seqid*) ; 

void nfs_increment_lock_seqid(int status, struct nfs_seqid *seqid)
{
	nfs_increment_seqid(status, seqid);
}