#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct section {int /*<<< orphan*/  entries_to_show; scalar_t__ show_all_entries; } ;
struct TYPE_6__ {size_t level; int /*<<< orphan*/ * nb_item; TYPE_1__* writer; struct section** section; } ;
typedef  TYPE_2__ WriterContext ;
struct TYPE_5__ {int /*<<< orphan*/  (* print_integer ) (TYPE_2__*,char const*,long long) ;} ;

/* Variables and functions */
 scalar_t__ av_dict_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char const*,long long) ; 

__attribute__((used)) static inline void writer_print_integer(WriterContext *wctx,
                                        const char *key, long long int val)
{
    const struct section *section = wctx->section[wctx->level];

    if (section->show_all_entries || av_dict_get(section->entries_to_show, key, NULL, 0)) {
        wctx->writer->print_integer(wctx, key, val);
        wctx->nb_item[wctx->level]++;
    }
}