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
typedef  int /*<<< orphan*/  uint32_t ;
struct inbuf {int dummy; } ;
struct data {int len; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 struct data data_grow_for (struct data,int) ; 
 struct data empty_data ; 
 int /*<<< orphan*/  flat_read_chunk (struct inbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flat_realign (struct inbuf*,int) ; 

__attribute__((used)) static struct data flat_read_data(struct inbuf *inb, int len)
{
	struct data d = empty_data;

	if (len == 0)
		return empty_data;

	d = data_grow_for(d, len);
	d.len = len;

	flat_read_chunk(inb, d.val, len);

	flat_realign(inb, sizeof(uint32_t));

	return d;
}