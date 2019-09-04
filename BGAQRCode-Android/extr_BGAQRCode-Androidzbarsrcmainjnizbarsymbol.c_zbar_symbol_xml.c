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
struct TYPE_3__ {unsigned char* data; int datalen; unsigned int modifiers; int configs; int cache_count; int /*<<< orphan*/  quality; int /*<<< orphan*/  orient; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zbar_symbol_t ;

/* Variables and functions */
 scalar_t__ MAX_CFG ; 
 unsigned int MAX_INT_DIGITS ; 
 scalar_t__ MAX_MOD ; 
 unsigned int MAX_STATIC ; 
 int /*<<< orphan*/  TMPL_COPY (char*) ; 
 int /*<<< orphan*/  TMPL_FMT (char*,...) ; 
 int ZBAR_CFG_ENABLE ; 
 int ZBAR_CFG_NUM ; 
 int ZBAR_MOD_NUM ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ base64_encode (char*,char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 unsigned int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (unsigned char*,char*,int) ; 
 int zbar_get_config_name (int) ; 
 int zbar_get_modifier_name (int) ; 
 char* zbar_get_orientation_name (int /*<<< orphan*/ ) ; 
 char* zbar_get_symbol_name (int /*<<< orphan*/ ) ; 

char *zbar_symbol_xml (const zbar_symbol_t *sym,
                       char **buf,
                       unsigned *len)
{
    unsigned int datalen, maxlen;
    int i, n = 0;

    const char *type = zbar_get_symbol_name(sym->type);
    const char *orient = zbar_get_orientation_name(sym->orient);

    /* check for binary data */
    unsigned char *data = (unsigned char*)sym->data;
    char binary = ((data[0] == 0xff && data[1] == 0xfe) ||
                   (data[0] == 0xfe && data[1] == 0xff) ||
                   !strncmp(sym->data, "<?xml", 5));
    for(i = 0; !binary && i < sym->datalen; i++) {
        unsigned char c = sym->data[i];
        binary = ((c < 0x20 && ((~0x00002600 >> c) & 1)) ||
                  (c >= 0x7f && c < 0xa0) ||
                  (c == ']' && i + 2 < sym->datalen &&
                   sym->data[i + 1] == ']' &&
                   sym->data[i + 2] == '>'));
    }

    datalen = strlen(sym->data);
    if(binary)
        datalen = (sym->datalen + 2) / 3 * 4 + sym->datalen / 57 + 3;

    maxlen = (MAX_STATIC + strlen(type) + strlen(orient) +
              datalen + MAX_INT_DIGITS + 1);
    unsigned int mods = sym->modifiers;
    if(mods)
        maxlen += MAX_MOD;
    unsigned int cfgs = sym->configs & ~(1 << ZBAR_CFG_ENABLE);
    if(cfgs)
        maxlen += MAX_CFG;
    if(binary)
        maxlen += MAX_INT_DIGITS;

    if(!*buf || (*len < maxlen)) {
        if(*buf)
            free(*buf);
        *buf = malloc(maxlen);
        /* FIXME check OOM */
        *len = maxlen;
    }

    TMPL_FMT("<symbol type='%s' quality='%d' orientation='%s'",
             type, sym->quality, orient);

    if(mods) {
        int j;
        TMPL_COPY(" modifiers='");
        for(j = 0; mods && j < ZBAR_MOD_NUM; j++, mods >>= 1)
            if(mods & 1)
                TMPL_FMT("%s ", zbar_get_modifier_name(j));
        /* cleanup trailing space */
        n--;
        TMPL_COPY("'");
    }

    if(cfgs) {
        int j;
        TMPL_COPY(" configs='");
        for(j = 0; cfgs && j < ZBAR_CFG_NUM; j++, cfgs >>= 1)
            if(cfgs & 1)
                TMPL_FMT("%s ", zbar_get_config_name(j));
        /* cleanup trailing space */
        n--;
        TMPL_COPY("'");
    }

    if(sym->cache_count)
        TMPL_FMT(" count='%d'", sym->cache_count);

    TMPL_COPY("><data");
    if(binary)
        TMPL_FMT(" format='base64' length='%d'", sym->datalen);
    TMPL_COPY("><![CDATA[");

    if(!binary) {
        memcpy(*buf + n, sym->data, sym->datalen + 1);
        n += sym->datalen;
    }
    else {
        TMPL_COPY("\n");
        n += base64_encode(*buf + n, sym->data, sym->datalen);
    }
    assert(n <= maxlen);

    TMPL_COPY("]]></data></symbol>");

    *len = n;
    return(*buf);
}