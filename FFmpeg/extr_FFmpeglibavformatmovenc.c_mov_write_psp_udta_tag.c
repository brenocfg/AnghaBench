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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  ascii_to_wc (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int language_code (char const*) ; 
 int utf8len (char const*) ; 

__attribute__((used)) static void mov_write_psp_udta_tag(AVIOContext *pb,
                                   const char *str, const char *lang, int type)
{
    int len = utf8len(str) + 1;
    if (len <= 0)
        return;
    avio_wb16(pb, len * 2 + 10);        /* size */
    avio_wb32(pb, type);                /* type */
    avio_wb16(pb, language_code(lang)); /* language */
    avio_wb16(pb, 0x01);                /* ? */
    ascii_to_wc(pb, str);
}