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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct coda_vattr {int dummy; } ;
struct CodaFid {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 struct inode* coda_iget (struct super_block*,struct CodaFid*,struct coda_vattr*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int venus_getattr (struct super_block*,struct CodaFid*,struct coda_vattr*) ; 

int coda_cnode_make(struct inode **inode, struct CodaFid *fid, struct super_block *sb)
{
        struct coda_vattr attr;
        int error;
        
	/* We get inode numbers from Venus -- see venus source */
	error = venus_getattr(sb, fid, &attr);
	if ( error ) {
	    *inode = NULL;
	    return error;
	} 

	*inode = coda_iget(sb, fid, &attr);
	if ( IS_ERR(*inode) ) {
		printk("coda_cnode_make: coda_iget failed\n");
                return PTR_ERR(*inode);
        }
	return 0;
}