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
typedef  int u_long ;
struct socket_data {int /*<<< orphan*/  mem_db; } ;
struct pcmcia_socket {int map_size; int /*<<< orphan*/  dev; struct socket_data* resource_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ checksum_match (struct pcmcia_socket*,int,int) ; 
 scalar_t__ cis_readable (struct pcmcia_socket*,int,int) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  sub_interval (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int do_mem_probe(u_long base, u_long num, struct pcmcia_socket *s)
{
    struct socket_data *s_data = s->resource_data;
    u_long i, j, bad, fail, step;

    dev_printk(KERN_INFO, &s->dev, "cs: memory probe 0x%06lx-0x%06lx:",
	       base, base+num-1);
    bad = fail = 0;
    step = (num < 0x20000) ? 0x2000 : ((num>>4) & ~0x1fff);
    /* don't allow too large steps */
    if (step > 0x800000)
	step = 0x800000;
    /* cis_readable wants to map 2x map_size */
    if (step < 2 * s->map_size)
	step = 2 * s->map_size;
    for (i = j = base; i < base+num; i = j + step) {
	if (!fail) {
	    for (j = i; j < base+num; j += step) {
		if (cis_readable(s, j, step))
		    break;
	    }
	    fail = ((i == base) && (j == base+num));
	}
	if (fail) {
	    for (j = i; j < base+num; j += 2*step)
		if (checksum_match(s, j, step) &&
		    checksum_match(s, j + step, step))
		    break;
	}
	if (i != j) {
	    if (!bad) printk(" excluding");
	    printk(" %#05lx-%#05lx", i, j-1);
	    sub_interval(&s_data->mem_db, i, j-i);
	    bad += j-i;
	}
    }
    printk(bad ? "\n" : " clean.\n");
    return (num - bad);
}