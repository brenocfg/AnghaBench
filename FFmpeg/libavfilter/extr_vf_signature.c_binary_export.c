#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_17__ {int** data; TYPE_5__* last; TYPE_4__* first; struct TYPE_17__* next; } ;
struct TYPE_16__ {int pts; int confidence; int* words; int* framesig; struct TYPE_16__* next; } ;
struct TYPE_10__ {int den; int num; } ;
struct TYPE_15__ {int lastindex; int w; int h; TYPE_7__* finesiglist; TYPE_8__* coarsesiglist; TYPE_3__* coarseend; TYPE_1__ time_base; } ;
struct TYPE_14__ {int index; int pts; } ;
struct TYPE_13__ {int index; int pts; } ;
struct TYPE_12__ {TYPE_2__* last; } ;
struct TYPE_11__ {int pts; } ;
typedef  TYPE_6__ StreamContext ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_7__ FineSignature ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_8__ CoarseSignature ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int SIGELEM_SIZE ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/ * av_malloc_array (int,int) ; 
 int /*<<< orphan*/  av_strerror (int,char*,int) ; 
 int /*<<< orphan*/  avpriv_align_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_bits32 (int /*<<< orphan*/ *,int) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int binary_export(AVFilterContext *ctx, StreamContext *sc, const char* filename)
{
    FILE* f;
    FineSignature* fs;
    CoarseSignature* cs;
    uint32_t numofsegments = (sc->lastindex + 44)/45;
    int i, j;
    PutBitContext buf;
    /* buffer + header + coarsesignatures + finesignature */
    int len = (512 + 6 * 32 + 3*16 + 2 +
        numofsegments * (4*32 + 1 + 5*243) +
        sc->lastindex * (2 + 32 + 6*8 + 608)) / 8;
    uint8_t* buffer = av_malloc_array(len, sizeof(uint8_t));
    if (!buffer)
        return AVERROR(ENOMEM);

    f = fopen(filename, "wb");
    if (!f) {
        int err = AVERROR(EINVAL);
        char buf[128];
        av_strerror(err, buf, sizeof(buf));
        av_log(ctx, AV_LOG_ERROR, "cannot open file %s: %s\n", filename, buf);
        av_freep(&buffer);
        return err;
    }
    init_put_bits(&buf, buffer, len);

    put_bits32(&buf, 1); /* NumOfSpatial Regions, only 1 supported */
    put_bits(&buf, 1, 1); /* SpatialLocationFlag, always the whole image */
    put_bits32(&buf, 0); /* PixelX,1 PixelY,1, 0,0 */
    put_bits(&buf, 16, sc->w-1 & 0xFFFF); /* PixelX,2 */
    put_bits(&buf, 16, sc->h-1 & 0xFFFF); /* PixelY,2 */
    put_bits32(&buf, 0); /* StartFrameOfSpatialRegion */
    put_bits32(&buf, sc->lastindex); /* NumOfFrames */
    /* hoping num is 1, other values are vague */
    /* den/num might be greater than 16 bit, so cutting it */
    put_bits(&buf, 16, 0xFFFF & (sc->time_base.den / sc->time_base.num)); /* MediaTimeUnit */
    put_bits(&buf, 1, 1); /* MediaTimeFlagOfSpatialRegion */
    put_bits32(&buf, 0); /* StartMediaTimeOfSpatialRegion */
    put_bits32(&buf, 0xFFFFFFFF & sc->coarseend->last->pts); /* EndMediaTimeOfSpatialRegion */
    put_bits32(&buf, numofsegments); /* NumOfSegments */
    /* coarsesignatures */
    for (cs = sc->coarsesiglist; cs; cs = cs->next) {
        put_bits32(&buf, cs->first->index); /* StartFrameOfSegment */
        put_bits32(&buf, cs->last->index); /* EndFrameOfSegment */
        put_bits(&buf, 1, 1); /* MediaTimeFlagOfSegment */
        put_bits32(&buf, 0xFFFFFFFF & cs->first->pts); /* StartMediaTimeOfSegment */
        put_bits32(&buf, 0xFFFFFFFF & cs->last->pts); /* EndMediaTimeOfSegment */
        for (i = 0; i < 5; i++) {
            /* put 243 bits ( = 7 * 32 + 19 = 8 * 28 + 19) into buffer */
            for (j = 0; j < 30; j++) {
                put_bits(&buf, 8, cs->data[i][j]);
            }
            put_bits(&buf, 3, cs->data[i][30] >> 5);
        }
    }
    /* finesignatures */
    put_bits(&buf, 1, 0); /* CompressionFlag, only 0 supported */
    for (fs = sc->finesiglist; fs; fs = fs->next) {
        put_bits(&buf, 1, 1); /* MediaTimeFlagOfFrame */
        put_bits32(&buf, 0xFFFFFFFF & fs->pts); /* MediaTimeOfFrame */
        put_bits(&buf, 8, fs->confidence); /* FrameConfidence */
        for (i = 0; i < 5; i++) {
            put_bits(&buf, 8, fs->words[i]); /* Words */
        }
        /* framesignature */
        for (i = 0; i < SIGELEM_SIZE/5; i++) {
            put_bits(&buf, 8, fs->framesig[i]);
        }
    }

    avpriv_align_put_bits(&buf);
    flush_put_bits(&buf);
    fwrite(buffer, 1, put_bits_count(&buf)/8, f);
    fclose(f);
    av_freep(&buffer);
    return 0;
}