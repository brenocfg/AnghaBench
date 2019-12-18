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
typedef  int /*<<< orphan*/  u32 ;
struct port {int /*<<< orphan*/  in_vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EPIPE ; 
 int /*<<< orphan*/  early_put_chars ; 
 int fill_readbuf (struct port*,char*,int,int) ; 
 struct port* find_port_by_vtermno (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_chars(u32 vtermno, char *buf, int count)
{
	struct port *port;

	/* If we've not set up the port yet, we have no input to give. */
	if (unlikely(early_put_chars))
		return 0;

	port = find_port_by_vtermno(vtermno);
	if (!port)
		return -EPIPE;

	/* If we don't have an input queue yet, we can't get input. */
	BUG_ON(!port->in_vq);

	return fill_readbuf(port, buf, count, false);
}