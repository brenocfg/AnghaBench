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
struct super_block {int dummy; } ;
typedef  int __u32 ;
struct TYPE_2__ {int (* s_hash_function ) (char const*,int) ;} ;

/* Variables and functions */
 int DOT_DOT_OFFSET ; 
 int DOT_OFFSET ; 
 int GET_HASH_VALUE (int) ; 
 int MAX_GENERATION_NUMBER ; 
 TYPE_1__* REISERFS_SB (struct super_block*) ; 
 int stub1 (char const*,int) ; 

__attribute__((used)) static __u32 get_third_component(struct super_block *s,
				 const char *name, int len)
{
	__u32 res;

	if (!len || (len == 1 && name[0] == '.'))
		return DOT_OFFSET;
	if (len == 2 && name[0] == '.' && name[1] == '.')
		return DOT_DOT_OFFSET;

	res = REISERFS_SB(s)->s_hash_function(name, len);

	// take bits from 7-th to 30-th including both bounds
	res = GET_HASH_VALUE(res);
	if (res == 0)
		// needed to have no names before "." and ".." those have hash
		// value == 0 and generation conters 1 and 2 accordingly
		res = 128;
	return res + MAX_GENERATION_NUMBER;
}