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
struct nfsd4_link {int li_namelen; int /*<<< orphan*/  li_name; } ;
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
 int /*<<< orphan*/  status ; 

__attribute__((used)) static __be32
nfsd4_decode_link(struct nfsd4_compoundargs *argp, struct nfsd4_link *link)
{
	DECODE_HEAD;

	READ_BUF(4);
	READ32(link->li_namelen);
	READ_BUF(link->li_namelen);
	SAVEMEM(link->li_name, link->li_namelen);
	if ((status = check_filename(link->li_name, link->li_namelen, nfserr_inval)))
		return status;

	DECODE_TAIL;
}