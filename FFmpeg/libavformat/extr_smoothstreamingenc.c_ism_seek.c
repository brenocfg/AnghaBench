#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {scalar_t__ start_pos; scalar_t__ size; int /*<<< orphan*/  infofile; int /*<<< orphan*/  file; } ;
struct TYPE_5__ {scalar_t__ cur_start_pos; int nb_fragments; scalar_t__ cur_pos; int /*<<< orphan*/ * out2; int /*<<< orphan*/ * out; TYPE_1__* ctx; int /*<<< orphan*/ * tail_out; TYPE_3__** fragments; } ;
struct TYPE_4__ {int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; } ;
typedef  TYPE_2__ OutputStream ;
typedef  TYPE_3__ Fragment ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 scalar_t__ AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOSYS ; 
 int SEEK_SET ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffurl_close (int /*<<< orphan*/ *) ; 
 int ffurl_open_whitelist (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffurl_seek (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int64_t ism_seek(void *opaque, int64_t offset, int whence)
{
    OutputStream *os = opaque;
    int i;
    if (whence != SEEK_SET)
        return AVERROR(ENOSYS);
    if (os->tail_out) {
        if (os->out) {
            ffurl_close(os->out);
        }
        if (os->out2) {
            ffurl_close(os->out2);
        }
        os->out = os->tail_out;
        os->out2 = NULL;
        os->tail_out = NULL;
    }
    if (offset >= os->cur_start_pos) {
        if (os->out)
            ffurl_seek(os->out, offset - os->cur_start_pos, SEEK_SET);
        os->cur_pos = offset;
        return offset;
    }
    for (i = os->nb_fragments - 1; i >= 0; i--) {
        Fragment *frag = os->fragments[i];
        if (offset >= frag->start_pos && offset < frag->start_pos + frag->size) {
            int ret;
            AVDictionary *opts = NULL;
            os->tail_out = os->out;
            av_dict_set(&opts, "truncate", "0", 0);
            ret = ffurl_open_whitelist(&os->out, frag->file, AVIO_FLAG_WRITE,
                                       &os->ctx->interrupt_callback, &opts, os->ctx->protocol_whitelist, os->ctx->protocol_blacklist, NULL);
            av_dict_free(&opts);
            if (ret < 0) {
                os->out = os->tail_out;
                os->tail_out = NULL;
                return ret;
            }
            av_dict_set(&opts, "truncate", "0", 0);
            ffurl_open_whitelist(&os->out2, frag->infofile, AVIO_FLAG_WRITE,
                                 &os->ctx->interrupt_callback, &opts, os->ctx->protocol_whitelist, os->ctx->protocol_blacklist, NULL);
            av_dict_free(&opts);
            ffurl_seek(os->out, offset - frag->start_pos, SEEK_SET);
            if (os->out2)
                ffurl_seek(os->out2, offset - frag->start_pos, SEEK_SET);
            os->cur_pos = offset;
            return offset;
        }
    }
    return AVERROR(EIO);
}