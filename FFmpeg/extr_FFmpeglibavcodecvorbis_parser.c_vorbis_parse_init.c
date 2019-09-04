#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int extradata_parsed; int valid_extradata; size_t* mode_blocksize; int /*<<< orphan*/ * blocksize; int /*<<< orphan*/  previous_blocksize; int /*<<< orphan*/ * class; } ;
typedef  TYPE_1__ AVVorbisParseContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int avpriv_split_xiph_headers (int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/  const**,int*) ; 
 int parse_id_header (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int parse_setup_header (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  vorbis_parser_class ; 

__attribute__((used)) static int vorbis_parse_init(AVVorbisParseContext *s,
                             const uint8_t *extradata, int extradata_size)
{
    const uint8_t *header_start[3];
    int header_len[3];
    int ret;

    s->class = &vorbis_parser_class;
    s->extradata_parsed = 1;

    if ((ret = avpriv_split_xiph_headers(extradata,
                                         extradata_size, 30,
                                         header_start, header_len)) < 0) {
        av_log(s, AV_LOG_ERROR, "Extradata corrupt.\n");
        return ret;
    }

    if ((ret = parse_id_header(s, header_start[0], header_len[0])) < 0)
        return ret;

    if ((ret = parse_setup_header(s, header_start[2], header_len[2])) < 0)
        return ret;

    s->valid_extradata = 1;
    s->previous_blocksize = s->blocksize[s->mode_blocksize[0]];

    return 0;
}