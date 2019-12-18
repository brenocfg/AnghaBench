#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char uint8_t ;
typedef  enum ID3v2Encoding { ____Placeholder_ID3v2Encoding } ID3v2Encoding ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int ID3v2_ENCODING_UTF16BOM ; 
 int avio_put_str (int /*<<< orphan*/ *,char const*) ; 
 int avio_put_str16le (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void id3v2_encode_string(AVIOContext *pb, const uint8_t *str,
                               enum ID3v2Encoding enc)
{
    int (*put)(AVIOContext*, const char*);

    if (enc == ID3v2_ENCODING_UTF16BOM) {
        avio_wl16(pb, 0xFEFF);      /* BOM */
        put = avio_put_str16le;
    } else
        put = avio_put_str;

    put(pb, str);
}