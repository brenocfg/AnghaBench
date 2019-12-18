#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ dma; } ;
struct TYPE_23__ {TYPE_7__* bottom; TYPE_5__* top; } ;
struct bttv {TYPE_12__ main; TYPE_11__* screen; TYPE_8__ curr; TYPE_3__* cvbi; } ;
struct TYPE_24__ {scalar_t__ dma; } ;
struct TYPE_21__ {scalar_t__ dma; } ;
struct TYPE_22__ {TYPE_6__ bottom; } ;
struct TYPE_19__ {scalar_t__ dma; } ;
struct TYPE_20__ {TYPE_4__ top; } ;
struct TYPE_17__ {scalar_t__ dma; } ;
struct TYPE_16__ {scalar_t__ dma; } ;
struct TYPE_18__ {TYPE_2__ bottom; TYPE_1__ top; } ;
struct TYPE_13__ {scalar_t__ dma; } ;
struct TYPE_14__ {TYPE_10__ bottom; TYPE_9__ top; } ;

/* Variables and functions */
 int /*<<< orphan*/  bttv_risc_disasm (struct bttv*,TYPE_12__*) ; 
 int /*<<< orphan*/  printk (char*,unsigned long long,...) ; 

__attribute__((used)) static void bttv_print_riscaddr(struct bttv *btv)
{
	printk("  main: %08Lx\n",
	       (unsigned long long)btv->main.dma);
	printk("  vbi : o=%08Lx e=%08Lx\n",
	       btv->cvbi ? (unsigned long long)btv->cvbi->top.dma : 0,
	       btv->cvbi ? (unsigned long long)btv->cvbi->bottom.dma : 0);
	printk("  cap : o=%08Lx e=%08Lx\n",
	       btv->curr.top    ? (unsigned long long)btv->curr.top->top.dma : 0,
	       btv->curr.bottom ? (unsigned long long)btv->curr.bottom->bottom.dma : 0);
	printk("  scr : o=%08Lx e=%08Lx\n",
	       btv->screen ? (unsigned long long)btv->screen->top.dma : 0,
	       btv->screen ? (unsigned long long)btv->screen->bottom.dma : 0);
	bttv_risc_disasm(btv, &btv->main);
}