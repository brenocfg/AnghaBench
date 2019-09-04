#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {double opacity; int /*<<< orphan*/  blend; void* mode; } ;
typedef  TYPE_1__ FilterParams ;

/* Variables and functions */
 void* BLEND_ADDITION ; 
 void* BLEND_AND ; 
 void* BLEND_AVERAGE ; 
 void* BLEND_DARKEN ; 
 void* BLEND_DIFFERENCE ; 
 void* BLEND_EXTREMITY ; 
 void* BLEND_GRAINEXTRACT ; 
 void* BLEND_GRAINMERGE ; 
 void* BLEND_HARDMIX ; 
 void* BLEND_LIGHTEN ; 
 void* BLEND_MULTIPLY ; 
 void* BLEND_NEGATION ; 
 void* BLEND_OR ; 
 void* BLEND_PHOENIX ; 
 void* BLEND_SCREEN ; 
 void* BLEND_SUBTRACT ; 
 void* BLEND_XOR ; 
 int /*<<< orphan*/  BUF_SIZE ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_blend_func (int) ; 
 scalar_t__ check_func (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_blend_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/  report (char*) ; 

void checkasm_check_blend(void)
{
    uint8_t *top1 = av_malloc(BUF_SIZE);
    uint8_t *top2 = av_malloc(BUF_SIZE);
    uint8_t *bot1 = av_malloc(BUF_SIZE);
    uint8_t *bot2 = av_malloc(BUF_SIZE);
    uint8_t *dst1 = av_malloc(BUF_SIZE);
    uint8_t *dst2 = av_malloc(BUF_SIZE);
    FilterParams param = {
        .opacity = 1.0,
    };

#define check_and_report(name, val, depth)        \
    param.mode = val;                             \
    ff_blend_init(&param, depth - 1);             \
    if (check_func(param.blend, #name))           \
        check_blend_func(depth);

    check_and_report(addition, BLEND_ADDITION, 1)
    check_and_report(grainmerge, BLEND_GRAINMERGE, 1)
    check_and_report(and, BLEND_AND, 1)
    check_and_report(average, BLEND_AVERAGE, 1)
    check_and_report(darken, BLEND_DARKEN, 1)
    check_and_report(grainextract, BLEND_GRAINEXTRACT, 1)
    check_and_report(hardmix, BLEND_HARDMIX, 1)
    check_and_report(lighten, BLEND_LIGHTEN, 1)
    check_and_report(multiply, BLEND_MULTIPLY, 1)
    check_and_report(or, BLEND_OR, 1)
    check_and_report(phoenix, BLEND_PHOENIX, 1)
    check_and_report(screen, BLEND_SCREEN, 1)
    check_and_report(subtract, BLEND_SUBTRACT, 1)
    check_and_report(xor, BLEND_XOR, 1)
    check_and_report(difference, BLEND_DIFFERENCE, 1)
    check_and_report(extremity, BLEND_EXTREMITY, 1)
    check_and_report(negation, BLEND_NEGATION, 1)

    report("8bit");

    check_and_report(addition_16, BLEND_ADDITION, 2)
    check_and_report(grainmerge_16, BLEND_GRAINMERGE, 2)
    check_and_report(and_16, BLEND_AND, 2)
    check_and_report(average_16, BLEND_AVERAGE, 2)
    check_and_report(darken_16, BLEND_DARKEN, 2)
    check_and_report(grainextract_16, BLEND_GRAINEXTRACT, 2)
    check_and_report(difference_16, BLEND_DIFFERENCE, 2)
    check_and_report(extremity_16, BLEND_EXTREMITY, 2)
    check_and_report(negation_16, BLEND_NEGATION, 2)
    check_and_report(lighten_16, BLEND_LIGHTEN, 2)
    check_and_report(or_16, BLEND_OR, 2)
    check_and_report(phoenix_16, BLEND_PHOENIX, 2)
    check_and_report(subtract_16, BLEND_SUBTRACT, 2)
    check_and_report(xor_16, BLEND_SUBTRACT, 2)

    report("16bit");

    av_freep(&top1);
    av_freep(&top2);
    av_freep(&bot1);
    av_freep(&bot2);
    av_freep(&dst1);
    av_freep(&dst2);
}