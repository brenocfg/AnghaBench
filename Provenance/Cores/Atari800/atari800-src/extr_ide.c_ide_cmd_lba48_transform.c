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
struct ide_device {int lba48; int nsector; int hob_nsector; } ;

/* Variables and functions */

__attribute__((used)) static void ide_cmd_lba48_transform(struct ide_device *s, int lba48) {
    s->lba48 = lba48;
    if (!s->lba48) {
        if (!s->nsector)
            s->nsector = 256;
    } else {
        if (!s->nsector && !s->hob_nsector)
            s->nsector = 65536;
        else      
            s->nsector = (s->hob_nsector << 8) | s->nsector;
    }
}