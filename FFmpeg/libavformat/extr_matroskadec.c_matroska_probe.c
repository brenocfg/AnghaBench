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
typedef  int uint64_t ;
struct TYPE_3__ {int* buf; int buf_size; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ AV_RB32 (int*) ; 
 scalar_t__ EBML_ID_HEADER ; 
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * matroska_doctypes ; 
 int /*<<< orphan*/  memcmp (int*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int matroska_probe(const AVProbeData *p)
{
    uint64_t total = 0;
    int len_mask = 0x80, size = 1, n = 1, i;

    /* EBML header? */
    if (AV_RB32(p->buf) != EBML_ID_HEADER)
        return 0;

    /* length of header */
    total = p->buf[4];
    while (size <= 8 && !(total & len_mask)) {
        size++;
        len_mask >>= 1;
    }
    if (size > 8)
        return 0;
    total &= (len_mask - 1);
    while (n < size)
        total = (total << 8) | p->buf[4 + n++];

    if (total + 1 == 1ULL << (7 * size)){
        /* Unknown-length header - simply parse the whole buffer. */
        total = p->buf_size - 4 - size;
    } else {
        /* Does the probe data contain the whole header? */
        if (p->buf_size < 4 + size + total)
            return 0;
    }

    /* The header should contain a known document type. For now,
     * we don't parse the whole header but simply check for the
     * availability of that array of characters inside the header.
     * Not fully fool-proof, but good enough. */
    for (i = 0; i < FF_ARRAY_ELEMS(matroska_doctypes); i++) {
        size_t probelen = strlen(matroska_doctypes[i]);
        if (total < probelen)
            continue;
        for (n = 4 + size; n <= 4 + size + total - probelen; n++)
            if (!memcmp(p->buf + n, matroska_doctypes[i], probelen))
                return AVPROBE_SCORE_MAX;
    }

    // probably valid EBML header but no recognized doctype
    return AVPROBE_SCORE_EXTENSION;
}