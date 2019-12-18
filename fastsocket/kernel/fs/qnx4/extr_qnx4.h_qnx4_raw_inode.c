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
struct qnx4_inode_entry {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct qnx4_inode_entry raw; } ;

/* Variables and functions */
 TYPE_1__* qnx4_i (struct inode*) ; 

__attribute__((used)) static inline struct qnx4_inode_entry *qnx4_raw_inode(struct inode *inode)
{
	return &qnx4_i(inode)->raw;
}