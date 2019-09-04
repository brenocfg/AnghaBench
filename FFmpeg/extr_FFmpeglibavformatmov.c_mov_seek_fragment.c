#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_10__ {int nb_items; TYPE_1__* item; int /*<<< orphan*/  complete; } ;
struct TYPE_9__ {TYPE_2__* priv_data; } ;
struct TYPE_8__ {TYPE_4__ frag_index; int /*<<< orphan*/  next_root_atom; } ;
struct TYPE_7__ {int /*<<< orphan*/  moof_offset; int /*<<< orphan*/  headers_read; } ;
typedef  TYPE_2__ MOVContext ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int mov_switch_root (TYPE_3__*,int,int) ; 
 int search_frag_timestamp (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_seek_fragment(AVFormatContext *s, AVStream *st, int64_t timestamp)
{
    MOVContext *mov = s->priv_data;
    int index;

    if (!mov->frag_index.complete)
        return 0;

    index = search_frag_timestamp(&mov->frag_index, st, timestamp);
    if (index < 0)
        index = 0;
    if (!mov->frag_index.item[index].headers_read)
        return mov_switch_root(s, -1, index);
    if (index + 1 < mov->frag_index.nb_items)
        mov->next_root_atom = mov->frag_index.item[index + 1].moof_offset;

    return 0;
}