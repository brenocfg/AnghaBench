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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_11__ {TYPE_1__* codecpar; } ;
struct TYPE_10__ {int /*<<< orphan*/  size; } ;
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {scalar_t__ codec_tag; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ MOVStreamContext ;
typedef  int /*<<< orphan*/  MOVContext ;
typedef  TYPE_3__ MOVAtom ;
typedef  TYPE_4__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ AV_RL32 (char*) ; 
 int /*<<< orphan*/  mov_read_glbl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__) ; 

__attribute__((used)) static void mov_parse_stsd_subtitle(MOVContext *c, AVIOContext *pb,
                                    AVStream *st, MOVStreamContext *sc,
                                    int64_t size)
{
    // ttxt stsd contains display flags, justification, background
    // color, fonts, and default styles, so fake an atom to read it
    MOVAtom fake_atom = { .size = size };
    // mp4s contains a regular esds atom
    if (st->codecpar->codec_tag != AV_RL32("mp4s"))
        mov_read_glbl(c, pb, fake_atom);
    st->codecpar->width  = sc->width;
    st->codecpar->height = sc->height;
}