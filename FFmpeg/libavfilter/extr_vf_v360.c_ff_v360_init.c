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
struct TYPE_4__ {int interp; int /*<<< orphan*/  remap_line; } ;
typedef  TYPE_1__ V360Context ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
#define  BICUBIC 131 
#define  BILINEAR 130 
#define  LANCZOS 129 
#define  NEAREST 128 
 int /*<<< orphan*/  ff_v360_init_x86 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  remap1_16bit_line_c ; 
 int /*<<< orphan*/  remap1_8bit_line_c ; 
 int /*<<< orphan*/  remap2_16bit_line_c ; 
 int /*<<< orphan*/  remap2_8bit_line_c ; 
 int /*<<< orphan*/  remap4_16bit_line_c ; 
 int /*<<< orphan*/  remap4_8bit_line_c ; 

void ff_v360_init(V360Context *s, int depth)
{
    switch (s->interp) {
    case NEAREST:
        s->remap_line = depth <= 8 ? remap1_8bit_line_c : remap1_16bit_line_c;
        break;
    case BILINEAR:
        s->remap_line = depth <= 8 ? remap2_8bit_line_c : remap2_16bit_line_c;
        break;
    case BICUBIC:
    case LANCZOS:
        s->remap_line = depth <= 8 ? remap4_8bit_line_c : remap4_16bit_line_c;
        break;
    }

    if (ARCH_X86)
        ff_v360_init_x86(s, depth);
}