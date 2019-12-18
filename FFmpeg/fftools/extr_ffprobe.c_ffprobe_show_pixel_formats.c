#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WriterContext ;
struct TYPE_7__ {int nb_components; int flags; int log2_chroma_w; int log2_chroma_h; TYPE_1__* comp; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int depth; } ;
typedef  TYPE_2__ AVPixFmtDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA ; 
 int AV_PIX_FMT_FLAG_RGB ; 
 int /*<<< orphan*/  BE ; 
 int /*<<< orphan*/  BITSTREAM ; 
 int /*<<< orphan*/  HWACCEL ; 
 int /*<<< orphan*/  PAL ; 
 int /*<<< orphan*/  PLANAR ; 
 int /*<<< orphan*/  PRINT_PIX_FMT_FLAG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PSEUDOPAL ; 
 int /*<<< orphan*/  RGB ; 
 int /*<<< orphan*/  SECTION_ID_PIXEL_FORMAT ; 
 int /*<<< orphan*/  SECTION_ID_PIXEL_FORMATS ; 
 int /*<<< orphan*/  SECTION_ID_PIXEL_FORMAT_COMPONENT ; 
 int /*<<< orphan*/  SECTION_ID_PIXEL_FORMAT_COMPONENTS ; 
 int /*<<< orphan*/  SECTION_ID_PIXEL_FORMAT_FLAGS ; 
 int av_get_bits_per_pixel (TYPE_2__ const*) ; 
 TYPE_2__* av_pix_fmt_desc_next (TYPE_2__ const*) ; 
 scalar_t__ do_show_pixel_format_components ; 
 scalar_t__ do_show_pixel_format_flags ; 
 int /*<<< orphan*/  print_int (char*,int) ; 
 int /*<<< orphan*/  print_str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_str_opt (char*,char*) ; 
 int /*<<< orphan*/  writer_print_section_footer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_print_section_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffprobe_show_pixel_formats(WriterContext *w)
{
    const AVPixFmtDescriptor *pixdesc = NULL;
    int i, n;

    writer_print_section_header(w, SECTION_ID_PIXEL_FORMATS);
    while (pixdesc = av_pix_fmt_desc_next(pixdesc)) {
        writer_print_section_header(w, SECTION_ID_PIXEL_FORMAT);
        print_str("name", pixdesc->name);
        print_int("nb_components", pixdesc->nb_components);
        if ((pixdesc->nb_components >= 3) && !(pixdesc->flags & AV_PIX_FMT_FLAG_RGB)) {
            print_int    ("log2_chroma_w", pixdesc->log2_chroma_w);
            print_int    ("log2_chroma_h", pixdesc->log2_chroma_h);
        } else {
            print_str_opt("log2_chroma_w", "N/A");
            print_str_opt("log2_chroma_h", "N/A");
        }
        n = av_get_bits_per_pixel(pixdesc);
        if (n) print_int    ("bits_per_pixel", n);
        else   print_str_opt("bits_per_pixel", "N/A");
        if (do_show_pixel_format_flags) {
            writer_print_section_header(w, SECTION_ID_PIXEL_FORMAT_FLAGS);
            PRINT_PIX_FMT_FLAG(BE,        "big_endian");
            PRINT_PIX_FMT_FLAG(PAL,       "palette");
            PRINT_PIX_FMT_FLAG(BITSTREAM, "bitstream");
            PRINT_PIX_FMT_FLAG(HWACCEL,   "hwaccel");
            PRINT_PIX_FMT_FLAG(PLANAR,    "planar");
            PRINT_PIX_FMT_FLAG(RGB,       "rgb");
#if FF_API_PSEUDOPAL
            PRINT_PIX_FMT_FLAG(PSEUDOPAL, "pseudopal");
#endif
            PRINT_PIX_FMT_FLAG(ALPHA,     "alpha");
            writer_print_section_footer(w);
        }
        if (do_show_pixel_format_components && (pixdesc->nb_components > 0)) {
            writer_print_section_header(w, SECTION_ID_PIXEL_FORMAT_COMPONENTS);
            for (i = 0; i < pixdesc->nb_components; i++) {
                writer_print_section_header(w, SECTION_ID_PIXEL_FORMAT_COMPONENT);
                print_int("index", i + 1);
                print_int("bit_depth", pixdesc->comp[i].depth);
                writer_print_section_footer(w);
            }
            writer_print_section_footer(w);
        }
        writer_print_section_footer(w);
    }
    writer_print_section_footer(w);
}