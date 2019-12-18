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
struct tty_struct {int count; scalar_t__ low_latency; int /*<<< orphan*/ * driver_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCLP_VT220_BUF_SIZE ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tty_struct* sclp_vt220_tty ; 

__attribute__((used)) static int
sclp_vt220_open(struct tty_struct *tty, struct file *filp)
{
	if (tty->count == 1) {
		sclp_vt220_tty = tty;
		tty->driver_data = kmalloc(SCLP_VT220_BUF_SIZE, GFP_KERNEL);
		if (tty->driver_data == NULL)
			return -ENOMEM;
		tty->low_latency = 0;
	}
	return 0;
}