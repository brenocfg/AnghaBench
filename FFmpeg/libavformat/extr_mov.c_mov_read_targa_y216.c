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
struct TYPE_10__ {int extradata_size; int /*<<< orphan*/ * extradata; void* width; void* height; } ;
struct TYPE_9__ {TYPE_2__* fc; } ;
struct TYPE_8__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_7__ {TYPE_4__* codecpar; } ;
typedef  TYPE_3__ MOVContext ;
typedef  int /*<<< orphan*/  MOVAtom ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVCodecParameters ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_TARGA_Y216 ; 
 void* AV_RB16 (int /*<<< orphan*/ *) ; 
 int mov_read_extradata (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_read_targa_y216(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    int ret = mov_read_extradata(c, pb, atom, AV_CODEC_ID_TARGA_Y216);

    if (!ret && c->fc->nb_streams >= 1) {
        AVCodecParameters *par = c->fc->streams[c->fc->nb_streams-1]->codecpar;
        if (par->extradata_size >= 40) {
            par->height = AV_RB16(&par->extradata[36]);
            par->width  = AV_RB16(&par->extradata[38]);
        }
    }
    return ret;
}