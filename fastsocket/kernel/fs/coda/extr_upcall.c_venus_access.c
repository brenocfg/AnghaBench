#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union outputArgs {int dummy; } outputArgs ;
struct CodaFid {int dummy; } ;
struct TYPE_2__ {int flags; struct CodaFid VFid; } ;
union inputArgs {TYPE_1__ coda_access; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_ACCESS ; 
 int /*<<< orphan*/  CODA_FREE (union inputArgs*,int) ; 
 int SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPARG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  access ; 
 int coda_upcall (int /*<<< orphan*/ ,int,int*,union inputArgs*) ; 
 int /*<<< orphan*/  coda_vcp (struct super_block*) ; 

int venus_access(struct super_block *sb, struct CodaFid *fid, int mask)
{
        union inputArgs *inp;
        union outputArgs *outp; 
	int insize, outsize, error;

	insize = SIZE(access);
	UPARG(CODA_ACCESS);

        inp->coda_access.VFid = *fid;
        inp->coda_access.flags = mask;

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);

	CODA_FREE(inp, insize);
	return error;
}