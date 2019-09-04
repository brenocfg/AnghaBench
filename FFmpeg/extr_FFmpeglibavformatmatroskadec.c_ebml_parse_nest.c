#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {double f; int /*<<< orphan*/  s; int /*<<< orphan*/  u; int /*<<< orphan*/  i; } ;
struct TYPE_6__ {int type; TYPE_1__ def; int /*<<< orphan*/  data_offset; scalar_t__ id; } ;
typedef  int /*<<< orphan*/  MatroskaDemuxContext ;
typedef  TYPE_2__ EbmlSyntax ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  EBML_FLOAT 132 
#define  EBML_SINT 131 
#define  EBML_STR 130 
#define  EBML_UINT 129 
#define  EBML_UTF8 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ebml_level_end (int /*<<< orphan*/ *) ; 
 int ebml_parse (int /*<<< orphan*/ *,TYPE_2__*,void*) ; 

__attribute__((used)) static int ebml_parse_nest(MatroskaDemuxContext *matroska, EbmlSyntax *syntax,
                           void *data)
{
    int i, res = 0;

    for (i = 0; syntax[i].id; i++)
        switch (syntax[i].type) {
        case EBML_SINT:
            *(int64_t *) ((char *) data + syntax[i].data_offset) = syntax[i].def.i;
            break;
        case EBML_UINT:
            *(uint64_t *) ((char *) data + syntax[i].data_offset) = syntax[i].def.u;
            break;
        case EBML_FLOAT:
            *(double *) ((char *) data + syntax[i].data_offset) = syntax[i].def.f;
            break;
        case EBML_STR:
        case EBML_UTF8:
            // the default may be NULL
            if (syntax[i].def.s) {
                uint8_t **dst = (uint8_t **) ((uint8_t *) data + syntax[i].data_offset);
                *dst = av_strdup(syntax[i].def.s);
                if (!*dst)
                    return AVERROR(ENOMEM);
            }
            break;
        }

    while (!res && !ebml_level_end(matroska))
        res = ebml_parse(matroska, syntax, data);

    return res;
}