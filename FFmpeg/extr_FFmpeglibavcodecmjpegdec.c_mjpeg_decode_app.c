#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int den; void* num; } ;
struct TYPE_10__ {int debug; TYPE_1__ sample_aspect_ratio; } ;
struct TYPE_9__ {int buggy_avid; int rgb; int pegasus_rct; scalar_t__ start_code; unsigned int iccnum; int* iccdatalens; unsigned int iccread; int /*<<< orphan*/  gb; TYPE_4__* avctx; scalar_t__* iccdata; int /*<<< orphan*/  exif_metadata; TYPE_5__* stereo3d; void* xfrm; void* colr; scalar_t__ got_picture; void* adobe_transform; } ;
typedef  TYPE_2__ MJpegDecodeContext ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 scalar_t__ APP1 ; 
 scalar_t__ APP2 ; 
 scalar_t__ APP3 ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_RB24 (char*) ; 
 int AV_RB32 (char*) ; 
 int AV_RL32 (char*) ; 
 int /*<<< orphan*/  AV_STEREO3D_2D ; 
 int /*<<< orphan*/  AV_STEREO3D_FLAG_INVERT ; 
 int /*<<< orphan*/  AV_STEREO3D_LINES ; 
 int /*<<< orphan*/  AV_STEREO3D_SIDEBYSIDE ; 
 int /*<<< orphan*/  AV_STEREO3D_TOPBOTTOM ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_DEBUG_PICT_INFO ; 
 int FF_DEBUG_STARTCODE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/ * align_get_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bswap32 (int) ; 
 int /*<<< orphan*/  av_fourcc2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (TYPE_5__**) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ av_malloc (int) ; 
 void* av_mallocz (unsigned int) ; 
 TYPE_5__* av_stereo3d_alloc () ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bytestream2_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 
 int ff_exif_decode_ifd (TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ff_tdecode_header (int /*<<< orphan*/ *,int*,int*) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 char show_bits (int /*<<< orphan*/ *,int) ; 
 int show_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mjpeg_decode_app(MJpegDecodeContext *s)
{
    int len, id, i;

    len = get_bits(&s->gb, 16);
    if (len < 6)
        return AVERROR_INVALIDDATA;
    if (8 * len > get_bits_left(&s->gb))
        return AVERROR_INVALIDDATA;

    id   = get_bits_long(&s->gb, 32);
    len -= 6;

    if (s->avctx->debug & FF_DEBUG_STARTCODE)
        av_log(s->avctx, AV_LOG_DEBUG, "APPx (%s / %8X) len=%d\n",
               av_fourcc2str(av_bswap32(id)), id, len);

    /* Buggy AVID, it puts EOI only at every 10th frame. */
    /* Also, this fourcc is used by non-avid files too, it holds some
       information, but it's always present in AVID-created files. */
    if (id == AV_RB32("AVI1")) {
        /* structure:
            4bytes      AVI1
            1bytes      polarity
            1bytes      always zero
            4bytes      field_size
            4bytes      field_size_less_padding
        */
            s->buggy_avid = 1;
        i = get_bits(&s->gb, 8); len--;
        av_log(s->avctx, AV_LOG_DEBUG, "polarity %d\n", i);
        goto out;
    }

    if (id == AV_RB32("JFIF")) {
        int t_w, t_h, v1, v2;
        if (len < 8)
            goto out;
        skip_bits(&s->gb, 8); /* the trailing zero-byte */
        v1 = get_bits(&s->gb, 8);
        v2 = get_bits(&s->gb, 8);
        skip_bits(&s->gb, 8);

        s->avctx->sample_aspect_ratio.num = get_bits(&s->gb, 16);
        s->avctx->sample_aspect_ratio.den = get_bits(&s->gb, 16);
        if (   s->avctx->sample_aspect_ratio.num <= 0
            || s->avctx->sample_aspect_ratio.den <= 0) {
            s->avctx->sample_aspect_ratio.num = 0;
            s->avctx->sample_aspect_ratio.den = 1;
        }

        if (s->avctx->debug & FF_DEBUG_PICT_INFO)
            av_log(s->avctx, AV_LOG_INFO,
                   "mjpeg: JFIF header found (version: %x.%x) SAR=%d/%d\n",
                   v1, v2,
                   s->avctx->sample_aspect_ratio.num,
                   s->avctx->sample_aspect_ratio.den);

        len -= 8;
        if (len >= 2) {
            t_w = get_bits(&s->gb, 8);
            t_h = get_bits(&s->gb, 8);
            if (t_w && t_h) {
                /* skip thumbnail */
                if (len -10 - (t_w * t_h * 3) > 0)
                    len -= t_w * t_h * 3;
            }
            len -= 2;
        }
        goto out;
    }

    if (   id == AV_RB32("Adob")
        && len >= 7
        && show_bits(&s->gb, 8) == 'e'
        && show_bits_long(&s->gb, 32) != AV_RB32("e_CM")) {
        skip_bits(&s->gb,  8); /* 'e' */
        skip_bits(&s->gb, 16); /* version */
        skip_bits(&s->gb, 16); /* flags0 */
        skip_bits(&s->gb, 16); /* flags1 */
        s->adobe_transform = get_bits(&s->gb,  8);
        if (s->avctx->debug & FF_DEBUG_PICT_INFO)
            av_log(s->avctx, AV_LOG_INFO, "mjpeg: Adobe header found, transform=%d\n", s->adobe_transform);
        len -= 7;
        goto out;
    }

    if (id == AV_RB32("LJIF")) {
        int rgb = s->rgb;
        int pegasus_rct = s->pegasus_rct;
        if (s->avctx->debug & FF_DEBUG_PICT_INFO)
            av_log(s->avctx, AV_LOG_INFO,
                   "Pegasus lossless jpeg header found\n");
        skip_bits(&s->gb, 16); /* version ? */
        skip_bits(&s->gb, 16); /* unknown always 0? */
        skip_bits(&s->gb, 16); /* unknown always 0? */
        skip_bits(&s->gb, 16); /* unknown always 0? */
        switch (i=get_bits(&s->gb, 8)) {
        case 1:
            rgb         = 1;
            pegasus_rct = 0;
            break;
        case 2:
            rgb         = 1;
            pegasus_rct = 1;
            break;
        default:
            av_log(s->avctx, AV_LOG_ERROR, "unknown colorspace %d\n", i);
        }

        len -= 9;
        if (s->got_picture)
            if (rgb != s->rgb || pegasus_rct != s->pegasus_rct) {
                av_log(s->avctx, AV_LOG_WARNING, "Mismatching LJIF tag\n");
                goto out;
            }

        s->rgb = rgb;
        s->pegasus_rct = pegasus_rct;

        goto out;
    }
    if (id == AV_RL32("colr") && len > 0) {
        s->colr = get_bits(&s->gb, 8);
        if (s->avctx->debug & FF_DEBUG_PICT_INFO)
            av_log(s->avctx, AV_LOG_INFO, "COLR %d\n", s->colr);
        len --;
        goto out;
    }
    if (id == AV_RL32("xfrm") && len > 0) {
        s->xfrm = get_bits(&s->gb, 8);
        if (s->avctx->debug & FF_DEBUG_PICT_INFO)
            av_log(s->avctx, AV_LOG_INFO, "XFRM %d\n", s->xfrm);
        len --;
        goto out;
    }

    /* JPS extension by VRex */
    if (s->start_code == APP3 && id == AV_RB32("_JPS") && len >= 10) {
        int flags, layout, type;
        if (s->avctx->debug & FF_DEBUG_PICT_INFO)
            av_log(s->avctx, AV_LOG_INFO, "_JPSJPS_\n");

        skip_bits(&s->gb, 32); len -= 4;  /* JPS_ */
        skip_bits(&s->gb, 16); len -= 2;  /* block length */
        skip_bits(&s->gb, 8);             /* reserved */
        flags  = get_bits(&s->gb, 8);
        layout = get_bits(&s->gb, 8);
        type   = get_bits(&s->gb, 8);
        len -= 4;

        av_freep(&s->stereo3d);
        s->stereo3d = av_stereo3d_alloc();
        if (!s->stereo3d) {
            goto out;
        }
        if (type == 0) {
            s->stereo3d->type = AV_STEREO3D_2D;
        } else if (type == 1) {
            switch (layout) {
            case 0x01:
                s->stereo3d->type = AV_STEREO3D_LINES;
                break;
            case 0x02:
                s->stereo3d->type = AV_STEREO3D_SIDEBYSIDE;
                break;
            case 0x03:
                s->stereo3d->type = AV_STEREO3D_TOPBOTTOM;
                break;
            }
            if (!(flags & 0x04)) {
                s->stereo3d->flags = AV_STEREO3D_FLAG_INVERT;
            }
        }
        goto out;
    }

    /* EXIF metadata */
    if (s->start_code == APP1 && id == AV_RB32("Exif") && len >= 2) {
        GetByteContext gbytes;
        int ret, le, ifd_offset, bytes_read;
        const uint8_t *aligned;

        skip_bits(&s->gb, 16); // skip padding
        len -= 2;

        // init byte wise reading
        aligned = align_get_bits(&s->gb);
        bytestream2_init(&gbytes, aligned, len);

        // read TIFF header
        ret = ff_tdecode_header(&gbytes, &le, &ifd_offset);
        if (ret) {
            av_log(s->avctx, AV_LOG_ERROR, "mjpeg: invalid TIFF header in EXIF data\n");
        } else {
            bytestream2_seek(&gbytes, ifd_offset, SEEK_SET);

            // read 0th IFD and store the metadata
            // (return values > 0 indicate the presence of subimage metadata)
            ret = ff_exif_decode_ifd(s->avctx, &gbytes, le, 0, &s->exif_metadata);
            if (ret < 0) {
                av_log(s->avctx, AV_LOG_ERROR, "mjpeg: error decoding EXIF data\n");
            }
        }

        bytes_read = bytestream2_tell(&gbytes);
        skip_bits(&s->gb, bytes_read << 3);
        len -= bytes_read;

        goto out;
    }

    /* Apple MJPEG-A */
    if ((s->start_code == APP1) && (len > (0x28 - 8))) {
        id   = get_bits_long(&s->gb, 32);
        len -= 4;
        /* Apple MJPEG-A */
        if (id == AV_RB32("mjpg")) {
            /* structure:
                4bytes      field size
                4bytes      pad field size
                4bytes      next off
                4bytes      quant off
                4bytes      huff off
                4bytes      image off
                4bytes      scan off
                4bytes      data off
            */
            if (s->avctx->debug & FF_DEBUG_PICT_INFO)
                av_log(s->avctx, AV_LOG_INFO, "mjpeg: Apple MJPEG-A header found\n");
        }
    }

    if (s->start_code == APP2 && id == AV_RB32("ICC_") && len >= 10) {
        int id2;
        unsigned seqno;
        unsigned nummarkers;

        id   = get_bits_long(&s->gb, 32);
        id2  = get_bits_long(&s->gb, 24);
        len -= 7;
        if (id != AV_RB32("PROF") || id2 != AV_RB24("ILE")) {
            av_log(s->avctx, AV_LOG_WARNING, "Invalid ICC_PROFILE header in APP2\n");
            goto out;
        }

        skip_bits(&s->gb, 8);
        seqno  = get_bits(&s->gb, 8);
        len   -= 2;
        if (seqno == 0) {
            av_log(s->avctx, AV_LOG_WARNING, "Invalid sequence number in APP2\n");
            goto out;
        }

        nummarkers  = get_bits(&s->gb, 8);
        len        -= 1;
        if (nummarkers == 0) {
            av_log(s->avctx, AV_LOG_WARNING, "Invalid number of markers coded in APP2\n");
            goto out;
        } else if (s->iccnum != 0 && nummarkers != s->iccnum) {
            av_log(s->avctx, AV_LOG_WARNING, "Mistmatch in coded number of ICC markers between markers\n");
            goto out;
        } else if (seqno > nummarkers) {
            av_log(s->avctx, AV_LOG_WARNING, "Mismatching sequence number and coded number of ICC markers\n");
            goto out;
        }

        /* Allocate if this is the first APP2 we've seen. */
        if (s->iccnum == 0) {
            s->iccdata     = av_mallocz(nummarkers * sizeof(*(s->iccdata)));
            s->iccdatalens = av_mallocz(nummarkers * sizeof(*(s->iccdatalens)));
            if (!s->iccdata || !s->iccdatalens) {
                av_log(s->avctx, AV_LOG_ERROR, "Could not allocate ICC data arrays\n");
                return AVERROR(ENOMEM);
            }
            s->iccnum = nummarkers;
        }

        if (s->iccdata[seqno - 1]) {
            av_log(s->avctx, AV_LOG_WARNING, "Duplicate ICC sequence number\n");
            goto out;
        }

        s->iccdatalens[seqno - 1]  = len;
        s->iccdata[seqno - 1]      = av_malloc(len);
        if (!s->iccdata[seqno - 1]) {
            av_log(s->avctx, AV_LOG_ERROR, "Could not allocate ICC data buffer\n");
            return AVERROR(ENOMEM);
        }

        memcpy(s->iccdata[seqno - 1], align_get_bits(&s->gb), len);
        skip_bits(&s->gb, len << 3);
        len = 0;
        s->iccread++;

        if (s->iccread > s->iccnum)
            av_log(s->avctx, AV_LOG_WARNING, "Read more ICC markers than are supposed to be coded\n");
    }

out:
    /* slow but needed for extreme adobe jpegs */
    if (len < 0)
        av_log(s->avctx, AV_LOG_ERROR,
               "mjpeg: error, decode_app parser read over the end\n");
    while (--len > 0)
        skip_bits(&s->gb, 8);

    return 0;
}