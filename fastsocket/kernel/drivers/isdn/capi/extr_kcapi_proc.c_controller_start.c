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
struct seq_file {int dummy; } ;
typedef  size_t loff_t ;

/* Variables and functions */
 size_t CAPI_MAXCONTR ; 
 void* capi_cards ; 

__attribute__((used)) static void *controller_start(struct seq_file *seq, loff_t *pos)
{
	if (*pos < CAPI_MAXCONTR)
		return &capi_cards[*pos];

	return NULL;
}