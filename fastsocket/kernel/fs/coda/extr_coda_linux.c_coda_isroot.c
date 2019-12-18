#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_2__* i_sb; } ;
struct TYPE_4__ {TYPE_1__* s_root; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */

int coda_isroot(struct inode *i)
{
    return ( i->i_sb->s_root->d_inode == i );
}