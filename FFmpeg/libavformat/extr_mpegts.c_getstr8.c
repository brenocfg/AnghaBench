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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  iso8859 ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_malloc (int) ; 
 int get8 (int const**,int const*) ; 
 int iconv (scalar_t__,char**,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  iconv_close (scalar_t__) ; 
 scalar_t__ iconv_open (char*,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,int const*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int const) ; 

__attribute__((used)) static char *getstr8(const uint8_t **pp, const uint8_t *p_end)
{
    int len;
    const uint8_t *p;
    char *str;

    p   = *pp;
    len = get8(&p, p_end);
    if (len < 0)
        return NULL;
    if (len > p_end - p)
        return NULL;
#if CONFIG_ICONV
    if (len) {
        const char *encodings[] = {
            "ISO6937", "ISO-8859-5", "ISO-8859-6", "ISO-8859-7",
            "ISO-8859-8", "ISO-8859-9", "ISO-8859-10", "ISO-8859-11",
            "", "ISO-8859-13", "ISO-8859-14", "ISO-8859-15", "", "", "", "",
            "", "UCS-2BE", "KSC_5601", "GB2312", "UCS-2BE", "UTF-8", "", "",
            "", "", "", "", "", "", "", ""
        };
        iconv_t cd;
        char *in, *out;
        size_t inlen = len, outlen = inlen * 6 + 1;
        if (len >= 3 && p[0] == 0x10 && !p[1] && p[2] && p[2] <= 0xf && p[2] != 0xc) {
            char iso8859[12];
            snprintf(iso8859, sizeof(iso8859), "ISO-8859-%d", p[2]);
            inlen -= 3;
            in = (char *)p + 3;
            cd = iconv_open("UTF-8", iso8859);
        } else if (p[0] < 0x20) {
            inlen -= 1;
            in = (char *)p + 1;
            cd = iconv_open("UTF-8", encodings[*p]);
        } else {
            in = (char *)p;
            cd = iconv_open("UTF-8", encodings[0]);
        }
        if (cd == (iconv_t)-1)
            goto no_iconv;
        str = out = av_malloc(outlen);
        if (!str) {
            iconv_close(cd);
            return NULL;
        }
        if (iconv(cd, &in, &inlen, &out, &outlen) == -1) {
            iconv_close(cd);
            av_freep(&str);
            goto no_iconv;
        }
        iconv_close(cd);
        *out = 0;
        *pp = p + len;
        return str;
    }
no_iconv:
#endif
    str = av_malloc(len + 1);
    if (!str)
        return NULL;
    memcpy(str, p, len);
    str[len] = '\0';
    p  += len;
    *pp = p;
    return str;
}