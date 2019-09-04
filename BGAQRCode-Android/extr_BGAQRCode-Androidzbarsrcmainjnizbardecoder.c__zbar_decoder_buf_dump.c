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

/* Variables and functions */
 char const* decoder_dump ; 
 int decoder_dumplen ; 
 int /*<<< orphan*/  free (char const*) ; 
 char* malloc (int) ; 
 int snprintf (char const*,int,char*,...) ; 

const char *_zbar_decoder_buf_dump (unsigned char *buf,
                                    unsigned int buflen)
{
    int dumplen = (buflen * 3) + 12;
    char *p;
    int i;

    if(!decoder_dump || dumplen > decoder_dumplen) {
        if(decoder_dump)
            free(decoder_dump);
        decoder_dump = malloc(dumplen);
        decoder_dumplen = dumplen;
    }
    p = decoder_dump +
        snprintf(decoder_dump, 12, "buf[%04x]=",
                 (buflen > 0xffff) ? 0xffff : buflen);
    for(i = 0; i < buflen; i++)
        p += snprintf(p, 4, "%s%02x", (i) ? " " : "",  buf[i]);
    return(decoder_dump);
}