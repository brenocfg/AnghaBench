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
struct nfsd4_read {int /*<<< orphan*/  rd_length; int /*<<< orphan*/  rd_offset; int /*<<< orphan*/  rd_stateid; } ;
struct nfsd4_compoundargs {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int /*<<< orphan*/  READ32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 scalar_t__ nfsd4_decode_stateid (struct nfsd4_compoundargs*,int /*<<< orphan*/ *) ; 
 scalar_t__ status ; 

__attribute__((used)) static __be32
nfsd4_decode_read(struct nfsd4_compoundargs *argp, struct nfsd4_read *read)
{
	DECODE_HEAD;

	status = nfsd4_decode_stateid(argp, &read->rd_stateid);
	if (status)
		return status;
	READ_BUF(12);
	READ64(read->rd_offset);
	READ32(read->rd_length);

	DECODE_TAIL;
}