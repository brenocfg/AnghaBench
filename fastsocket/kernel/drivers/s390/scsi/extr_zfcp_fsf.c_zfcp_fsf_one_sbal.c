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
struct scatterlist {scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ sg_is_last (struct scatterlist*) ; 

__attribute__((used)) static int zfcp_fsf_one_sbal(struct scatterlist *sg)
{
	return sg_is_last(sg) && sg->length <= PAGE_SIZE;
}