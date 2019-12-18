#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
struct TYPE_9__ {int extradata_size; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/  fc; } ;
typedef  TYPE_1__ MOVContext ;
typedef  TYPE_2__ MOVAtom ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVCodecParameters ;

/* Variables and functions */
 int /*<<< orphan*/  AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_WB32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ffio_read_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t mov_read_atom_into_extradata(MOVContext *c, AVIOContext *pb, MOVAtom atom,
                                        AVCodecParameters *par, uint8_t *buf)
{
    int64_t result = atom.size;
    int err;

    AV_WB32(buf    , atom.size + 8);
    AV_WL32(buf + 4, atom.type);
    err = ffio_read_size(pb, buf + 8, atom.size);
    if (err < 0) {
        par->extradata_size -= atom.size;
        return err;
    } else if (err < atom.size) {
        av_log(c->fc, AV_LOG_WARNING, "truncated extradata\n");
        par->extradata_size -= atom.size - err;
        result = err;
    }
    memset(buf + 8 + err, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    return result;
}