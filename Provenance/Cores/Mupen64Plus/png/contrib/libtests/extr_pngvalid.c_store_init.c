#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * prev; } ;
struct TYPE_7__ {int chunkpos; int chunklen; scalar_t__ noptions; scalar_t__ npalette; int /*<<< orphan*/ * palette; TYPE_1__ new; scalar_t__ IDAT_bits; scalar_t__ IDAT_size; scalar_t__ chunktype; scalar_t__ writepos; int /*<<< orphan*/ * piwrite; int /*<<< orphan*/ * pwrite; scalar_t__ image_h; scalar_t__ cb_row; scalar_t__ cb_image; int /*<<< orphan*/ * image; scalar_t__ readpos; int /*<<< orphan*/ * next; int /*<<< orphan*/ * current; int /*<<< orphan*/  saved; int /*<<< orphan*/ * piread; int /*<<< orphan*/ * pread; scalar_t__ nwarnings; scalar_t__ nerrors; scalar_t__ validated; scalar_t__ progressive; scalar_t__ speed; scalar_t__ saw_warning; scalar_t__ expect_warning; scalar_t__ expect_error; scalar_t__ treat_warnings_as_errors; scalar_t__ verbose; int /*<<< orphan*/  write_memory_pool; int /*<<< orphan*/  read_memory_pool; int /*<<< orphan*/  exception_context; } ;
typedef  TYPE_2__ png_store ;

/* Variables and functions */
 int /*<<< orphan*/  init_exception_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_pool_init (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
store_init(png_store* ps)
{
   memset(ps, 0, sizeof *ps);
   init_exception_context(&ps->exception_context);
   store_pool_init(ps, &ps->read_memory_pool);
   store_pool_init(ps, &ps->write_memory_pool);
   ps->verbose = 0;
   ps->treat_warnings_as_errors = 0;
   ps->expect_error = 0;
   ps->expect_warning = 0;
   ps->saw_warning = 0;
   ps->speed = 0;
   ps->progressive = 0;
   ps->validated = 0;
   ps->nerrors = ps->nwarnings = 0;
   ps->pread = NULL;
   ps->piread = NULL;
   ps->saved = ps->current = NULL;
   ps->next = NULL;
   ps->readpos = 0;
   ps->image = NULL;
   ps->cb_image = 0;
   ps->cb_row = 0;
   ps->image_h = 0;
   ps->pwrite = NULL;
   ps->piwrite = NULL;
   ps->writepos = 0;
   ps->chunkpos = 8;
   ps->chunktype = 0;
   ps->chunklen = 16;
   ps->IDAT_size = 0;
   ps->IDAT_bits = 0;
   ps->new.prev = NULL;
   ps->palette = NULL;
   ps->npalette = 0;
   ps->noptions = 0;
}