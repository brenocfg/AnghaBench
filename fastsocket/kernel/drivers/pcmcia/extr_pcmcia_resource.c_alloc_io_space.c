#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct pcmcia_socket {int features; unsigned int io_offset; TYPE_1__* io; } ;
struct TYPE_5__ {unsigned int start; int flags; int end; } ;
struct TYPE_4__ {unsigned int InUse; TYPE_2__* res; } ;

/* Variables and functions */
 int IORESOURCE_BITS ; 
 int MAX_IO_WIN ; 
 int SS_CAP_STATIC_MAP ; 
 int /*<<< orphan*/  ds_dbg (struct pcmcia_socket*,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 scalar_t__ pcmcia_adjust_io_region (TYPE_2__*,unsigned int,unsigned int,struct pcmcia_socket*) ; 
 TYPE_2__* pcmcia_find_io_region (unsigned int,unsigned int,unsigned int,struct pcmcia_socket*) ; 

__attribute__((used)) static int alloc_io_space(struct pcmcia_socket *s, u_int attr,
			  unsigned int *base, unsigned int num, u_int lines)
{
	int i;
	unsigned int try, align;

	align = (*base) ? (lines ? 1<<lines : 0) : 1;
	if (align && (align < num)) {
		if (*base) {
			ds_dbg(s, 0, "odd IO request: num %#x align %#x\n",
			       num, align);
			align = 0;
		} else
			while (align && (align < num)) align <<= 1;
	}
	if (*base & ~(align-1)) {
		ds_dbg(s, 0, "odd IO request: base %#x align %#x\n",
		       *base, align);
		align = 0;
	}
	if ((s->features & SS_CAP_STATIC_MAP) && s->io_offset) {
		*base = s->io_offset | (*base & 0x0fff);
		return 0;
	}
	/* Check for an already-allocated window that must conflict with
	 * what was asked for.  It is a hack because it does not catch all
	 * potential conflicts, just the most obvious ones.
	 */
	for (i = 0; i < MAX_IO_WIN; i++)
		if ((s->io[i].res) && *base &&
		    ((s->io[i].res->start & (align-1)) == *base))
			return 1;
	for (i = 0; i < MAX_IO_WIN; i++) {
		if (!s->io[i].res) {
			s->io[i].res = pcmcia_find_io_region(*base, num, align, s);
			if (s->io[i].res) {
				*base = s->io[i].res->start;
				s->io[i].res->flags = (s->io[i].res->flags & ~IORESOURCE_BITS) | (attr & IORESOURCE_BITS);
				s->io[i].InUse = num;
				break;
			} else
				return 1;
		} else if ((s->io[i].res->flags & IORESOURCE_BITS) != (attr & IORESOURCE_BITS))
			continue;
		/* Try to extend top of window */
		try = s->io[i].res->end + 1;
		if ((*base == 0) || (*base == try))
			if (pcmcia_adjust_io_region(s->io[i].res, s->io[i].res->start,
						    s->io[i].res->end + num, s) == 0) {
				*base = try;
				s->io[i].InUse += num;
				break;
			}
		/* Try to extend bottom of window */
		try = s->io[i].res->start - num;
		if ((*base == 0) || (*base == try))
			if (pcmcia_adjust_io_region(s->io[i].res, s->io[i].res->start - num,
						    s->io[i].res->end, s) == 0) {
				*base = try;
				s->io[i].InUse += num;
				break;
			}
	}
	return (i == MAX_IO_WIN);
}