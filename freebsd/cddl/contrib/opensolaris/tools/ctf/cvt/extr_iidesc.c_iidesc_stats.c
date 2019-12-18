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
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 scalar_t__ II_GFUN ; 
 scalar_t__ II_GVAR ; 
 scalar_t__ II_SFUN ; 
 scalar_t__ II_SOU ; 
 scalar_t__ II_SVAR ; 
 scalar_t__ II_TYPE ; 
 int hash_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  iidesc_count_type ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int) ; 

void
iidesc_stats(hash_t *ii)
{
	printf("GFun: %5d SFun: %5d GVar: %5d SVar: %5d T %5d SOU: %5d\n",
	    hash_iter(ii, iidesc_count_type, (void *)II_GFUN),
	    hash_iter(ii, iidesc_count_type, (void *)II_SFUN),
	    hash_iter(ii, iidesc_count_type, (void *)II_GVAR),
	    hash_iter(ii, iidesc_count_type, (void *)II_SVAR),
	    hash_iter(ii, iidesc_count_type, (void *)II_TYPE),
	    hash_iter(ii, iidesc_count_type, (void *)II_SOU));
}