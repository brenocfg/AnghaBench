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
struct inode {int dummy; } ;
struct ima_iint_cache {int flags; } ;

/* Variables and functions */
 int EACCES ; 
 int IMA_MEASURED ; 
 int ima_match_policy (struct inode*,int,int) ; 

int ima_must_measure(struct ima_iint_cache *iint, struct inode *inode,
		     int mask, int function)
{
	int must_measure;

	if (iint->flags & IMA_MEASURED)
		return 1;

	must_measure = ima_match_policy(inode, function, mask);
	return must_measure ? 0 : -EACCES;
}