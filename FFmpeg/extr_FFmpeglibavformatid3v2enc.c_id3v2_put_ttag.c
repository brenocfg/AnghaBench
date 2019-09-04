#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  enum ID3v2Encoding { ____Placeholder_ID3v2Encoding } ID3v2Encoding ;
struct TYPE_3__ {int version; } ;
typedef  TYPE_1__ ID3v2EncContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int ID3v2_ENCODING_ISO8859 ; 
 int ID3v2_ENCODING_UTF16BOM ; 
 int ID3v2_HEADER_SIZE ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  id3v2_encode_string (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  id3v2_put_size (int /*<<< orphan*/ *,int) ; 
 scalar_t__ string_is_ascii (char const*) ; 

__attribute__((used)) static int id3v2_put_ttag(ID3v2EncContext *id3, AVIOContext *avioc, const char *str1, const char *str2,
                          uint32_t tag, enum ID3v2Encoding enc)
{
    int len;
    uint8_t *pb;
    AVIOContext *dyn_buf;
    if (avio_open_dyn_buf(&dyn_buf) < 0)
        return AVERROR(ENOMEM);

    /* check if the strings are ASCII-only and use UTF16 only if
     * they're not */
    if (enc == ID3v2_ENCODING_UTF16BOM && string_is_ascii(str1) &&
        (!str2 || string_is_ascii(str2)))
        enc = ID3v2_ENCODING_ISO8859;

    avio_w8(dyn_buf, enc);
    id3v2_encode_string(dyn_buf, str1, enc);
    if (str2)
        id3v2_encode_string(dyn_buf, str2, enc);
    len = avio_close_dyn_buf(dyn_buf, &pb);

    avio_wb32(avioc, tag);
    /* ID3v2.3 frame size is not sync-safe */
    if (id3->version == 3)
        avio_wb32(avioc, len);
    else
        id3v2_put_size(avioc, len);
    avio_wb16(avioc, 0);
    avio_write(avioc, pb, len);

    av_freep(&pb);
    return len + ID3v2_HEADER_SIZE;
}