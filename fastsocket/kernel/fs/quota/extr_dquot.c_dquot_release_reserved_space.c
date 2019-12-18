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
typedef  int /*<<< orphan*/  qsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DQUOT_SPACE_RESERVE ; 
 int /*<<< orphan*/  __dquot_free_space (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dquot_release_reserved_space(struct inode *inode, qsize_t number)
{
	__dquot_free_space(inode, number, DQUOT_SPACE_RESERVE);

}