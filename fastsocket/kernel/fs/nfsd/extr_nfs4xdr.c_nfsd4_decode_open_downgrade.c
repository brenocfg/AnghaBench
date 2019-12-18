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
struct nfsd4_open_downgrade {int /*<<< orphan*/  od_share_deny; int /*<<< orphan*/  od_share_access; int /*<<< orphan*/  od_seqid; int /*<<< orphan*/  od_stateid; int /*<<< orphan*/ * od_stateowner; } ;
struct nfsd4_compoundargs {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int /*<<< orphan*/  READ32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 scalar_t__ nfsd4_decode_stateid (struct nfsd4_compoundargs*,int /*<<< orphan*/ *) ; 
 scalar_t__ status ; 

__attribute__((used)) static __be32
nfsd4_decode_open_downgrade(struct nfsd4_compoundargs *argp, struct nfsd4_open_downgrade *open_down)
{
	DECODE_HEAD;
		    
	open_down->od_stateowner = NULL;
	status = nfsd4_decode_stateid(argp, &open_down->od_stateid);
	if (status)
		return status;
	READ_BUF(12);
	READ32(open_down->od_seqid);
	READ32(open_down->od_share_access);
	READ32(open_down->od_share_deny);
						        
	DECODE_TAIL;
}