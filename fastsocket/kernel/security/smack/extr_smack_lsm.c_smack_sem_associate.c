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
struct sem_array {int dummy; } ;

/* Variables and functions */
 int smack_flags_to_may (int) ; 
 int smk_curacc_sem (struct sem_array*,int) ; 

__attribute__((used)) static int smack_sem_associate(struct sem_array *sma, int semflg)
{
	int may;

	may = smack_flags_to_may(semflg);
	return smk_curacc_sem(sma, may);
}