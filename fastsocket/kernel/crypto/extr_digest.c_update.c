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
struct scatterlist {int dummy; } ;
struct hash_desc {int dummy; } ;

/* Variables and functions */
 int EDEADLK ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_irq () ; 
 int update2 (struct hash_desc*,struct scatterlist*,unsigned int) ; 

__attribute__((used)) static int update(struct hash_desc *desc,
		  struct scatterlist *sg, unsigned int nbytes)
{
	if (WARN_ON_ONCE(in_irq()))
		return -EDEADLK;
	return update2(desc, sg, nbytes);
}