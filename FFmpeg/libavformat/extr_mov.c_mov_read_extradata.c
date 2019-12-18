#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_11__ {int codec_id; scalar_t__ extradata; scalar_t__ extradata_size; } ;
struct TYPE_10__ {TYPE_4__* codecpar; } ;
struct TYPE_9__ {TYPE_1__* fc; } ;
struct TYPE_8__ {int nb_streams; TYPE_3__** streams; } ;
typedef  TYPE_2__ MOVContext ;
typedef  int /*<<< orphan*/  MOVAtom ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int mov_read_atom_into_extradata (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,scalar_t__) ; 
 int mov_realloc_extradata (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_read_extradata(MOVContext *c, AVIOContext *pb, MOVAtom atom,
                              enum AVCodecID codec_id)
{
    AVStream *st;
    uint64_t original_size;
    int err;

    if (c->fc->nb_streams < 1) // will happen with jp2 files
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];

    if (st->codecpar->codec_id != codec_id)
        return 0; /* unexpected codec_id - don't mess with extradata */

    original_size = st->codecpar->extradata_size;
    err = mov_realloc_extradata(st->codecpar, atom);
    if (err)
        return err;

    err =  mov_read_atom_into_extradata(c, pb, atom, st->codecpar,  st->codecpar->extradata + original_size);
    if (err < 0)
        return err;
    return 0; // Note: this is the original behavior to ignore truncation.
}