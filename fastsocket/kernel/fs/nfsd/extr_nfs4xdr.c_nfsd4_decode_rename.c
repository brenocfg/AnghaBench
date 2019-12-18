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
struct nfsd4_rename {int rn_snamelen; int rn_tnamelen; int /*<<< orphan*/  rn_tname; int /*<<< orphan*/  rn_sname; } ;
struct nfsd4_compoundargs {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int /*<<< orphan*/  READ32 (int) ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 int /*<<< orphan*/  SAVEMEM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_filename (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfserr_inval ; 
 int /*<<< orphan*/  nfserr_noent ; 
 int /*<<< orphan*/  status ; 

__attribute__((used)) static __be32
nfsd4_decode_rename(struct nfsd4_compoundargs *argp, struct nfsd4_rename *rename)
{
	DECODE_HEAD;

	READ_BUF(4);
	READ32(rename->rn_snamelen);
	READ_BUF(rename->rn_snamelen + 4);
	SAVEMEM(rename->rn_sname, rename->rn_snamelen);
	READ32(rename->rn_tnamelen);
	READ_BUF(rename->rn_tnamelen);
	SAVEMEM(rename->rn_tname, rename->rn_tnamelen);
	if ((status = check_filename(rename->rn_sname, rename->rn_snamelen, nfserr_noent)))
		return status;
	if ((status = check_filename(rename->rn_tname, rename->rn_tnamelen, nfserr_inval)))
		return status;

	DECODE_TAIL;
}