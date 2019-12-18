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
struct resource_map {int /*<<< orphan*/  num; int /*<<< orphan*/  base; struct resource_map* next; } ;
struct socket_data {struct resource_map mem_db; } ;
struct pcmcia_socket {struct socket_data* resource_data; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ do_mem_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pcmcia_socket*) ; 

__attribute__((used)) static int validate_mem(struct pcmcia_socket *s, unsigned int probe_mask)
{
	struct resource_map *m, mm;
	struct socket_data *s_data = s->resource_data;
	unsigned long ok = 0;

	for (m = s_data->mem_db.next; m != &s_data->mem_db; m = mm.next) {
		mm = *m;
		ok += do_mem_probe(mm.base, mm.num, s);
	}
	if (ok > 0)
		return 0;
	return -ENODEV;
}