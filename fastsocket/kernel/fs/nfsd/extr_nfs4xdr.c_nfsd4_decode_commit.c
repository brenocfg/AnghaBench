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
struct nfsd4_compoundargs {int dummy; } ;
struct nfsd4_commit {int /*<<< orphan*/  co_count; int /*<<< orphan*/  co_offset; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int /*<<< orphan*/  READ32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_BUF (int) ; 

__attribute__((used)) static __be32
nfsd4_decode_commit(struct nfsd4_compoundargs *argp, struct nfsd4_commit *commit)
{
	DECODE_HEAD;

	READ_BUF(12);
	READ64(commit->co_offset);
	READ32(commit->co_count);

	DECODE_TAIL;
}