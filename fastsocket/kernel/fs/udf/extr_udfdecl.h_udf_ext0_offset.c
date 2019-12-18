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
struct inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ i_alloc_type; } ;

/* Variables and functions */
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 TYPE_1__* UDF_I (struct inode*) ; 
 size_t udf_file_entry_alloc_offset (struct inode*) ; 

__attribute__((used)) static inline size_t udf_ext0_offset(struct inode *inode)
{
	if (UDF_I(inode)->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		return udf_file_entry_alloc_offset(inode);
	else
		return 0;
}