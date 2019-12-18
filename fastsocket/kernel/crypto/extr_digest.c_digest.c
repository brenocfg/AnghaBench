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
typedef  int /*<<< orphan*/  u8 ;
struct scatterlist {int dummy; } ;
struct hash_desc {int dummy; } ;

/* Variables and functions */
 int EDEADLK ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int final (struct hash_desc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_irq () ; 
 int /*<<< orphan*/  init (struct hash_desc*) ; 
 int /*<<< orphan*/  update2 (struct hash_desc*,struct scatterlist*,unsigned int) ; 

__attribute__((used)) static int digest(struct hash_desc *desc,
		  struct scatterlist *sg, unsigned int nbytes, u8 *out)
{
	if (WARN_ON_ONCE(in_irq()))
		return -EDEADLK;

	init(desc);
	update2(desc, sg, nbytes);
	return final(desc, out);
}