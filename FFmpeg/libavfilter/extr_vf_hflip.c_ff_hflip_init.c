#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * flip_line; } ;
typedef  TYPE_1__ FlipContext ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 int AVERROR_BUG ; 
 int /*<<< orphan*/  ff_hflip_init_x86 (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  hflip_b24_c ; 
 int /*<<< orphan*/  hflip_b48_c ; 
 int /*<<< orphan*/  hflip_byte_c ; 
 int /*<<< orphan*/  hflip_dword_c ; 
 int /*<<< orphan*/  hflip_qword_c ; 
 int /*<<< orphan*/  hflip_short_c ; 

int ff_hflip_init(FlipContext *s, int step[4], int nb_planes)
{
    int i;

    for (i = 0; i < nb_planes; i++) {
        switch (step[i]) {
        case 1: s->flip_line[i] = hflip_byte_c;  break;
        case 2: s->flip_line[i] = hflip_short_c; break;
        case 3: s->flip_line[i] = hflip_b24_c;   break;
        case 4: s->flip_line[i] = hflip_dword_c; break;
        case 6: s->flip_line[i] = hflip_b48_c;   break;
        case 8: s->flip_line[i] = hflip_qword_c; break;
        default:
            return AVERROR_BUG;
        }
    }
    if (ARCH_X86)
        ff_hflip_init_x86(s, step, nb_planes);

    return 0;
}