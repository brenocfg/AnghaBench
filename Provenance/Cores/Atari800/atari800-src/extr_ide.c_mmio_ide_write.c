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
typedef  int uint8_t ;
struct ide_device {int* upperhalf; int cycle; int data; int /*<<< orphan*/  do_8bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ide_data_writew (struct ide_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ide_ioport_write (struct ide_device*,int,int) ; 

__attribute__((used)) static void mmio_ide_write(struct ide_device *s, int addr, uint8_t val) {
    addr &= 15;

    if (addr == 0) {
        if (!s->do_8bit) {
            ide_data_writew(s, 0, s->upperhalf[0] | val);
            return;
        }
        if (!s->cycle) {
            s->data = val & 0xff;
        } else {
            ide_data_writew(s, 0, s->data | (val << 8));
        }
        s->cycle = !s->cycle;
    } else if (addr >= 8) {
        s->upperhalf[addr-8] = val << 8;
    } else {
        ide_ioport_write(s, addr, s->upperhalf[addr] | val);
    }
}