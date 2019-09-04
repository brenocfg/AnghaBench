#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_9__ {scalar_t__ eof_reached; } ;
struct TYPE_8__ {int current_id; TYPE_1__* ctx; scalar_t__ is_live; } ;
struct TYPE_7__ {TYPE_4__* pb; } ;
typedef  TYPE_2__ MatroskaDemuxContext ;
typedef  int /*<<< orphan*/  EbmlSyntax ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int ebml_parse_id (TYPE_2__*,int /*<<< orphan*/ *,int,void*) ; 
 int ebml_read_num (TYPE_2__*,TYPE_4__*,int,int*) ; 

__attribute__((used)) static int ebml_parse(MatroskaDemuxContext *matroska, EbmlSyntax *syntax,
                      void *data)
{
    if (!matroska->current_id) {
        uint64_t id;
        int res = ebml_read_num(matroska, matroska->ctx->pb, 4, &id);
        if (res < 0) {
            // in live mode, finish parsing if EOF is reached.
            return (matroska->is_live && matroska->ctx->pb->eof_reached &&
                    res == AVERROR_EOF) ? 1 : res;
        }
        matroska->current_id = id | 1 << 7 * res;
    }
    return ebml_parse_id(matroska, syntax, matroska->current_id, data);
}