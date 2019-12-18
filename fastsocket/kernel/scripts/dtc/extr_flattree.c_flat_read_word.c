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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  uint32_t ;
struct inbuf {int ptr; int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fdt32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flat_read_chunk (struct inbuf*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint32_t flat_read_word(struct inbuf *inb)
{
	uint32_t val;

	assert(((inb->ptr - inb->base) % sizeof(val)) == 0);

	flat_read_chunk(inb, &val, sizeof(val));

	return fdt32_to_cpu(val);
}