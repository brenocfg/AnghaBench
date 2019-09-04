#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * metadata; } ;
struct TYPE_13__ {int nb_chapters; int nb_programs; int nb_streams; TYPE_9__** streams; TYPE_2__** programs; TYPE_1__** chapters; int /*<<< orphan*/ * metadata; } ;
struct TYPE_12__ {int metadata_global_manual; int metadata_streams_manual; int metadata_chapters_manual; } ;
struct TYPE_11__ {int /*<<< orphan*/ * metadata; } ;
struct TYPE_10__ {int /*<<< orphan*/ * metadata; } ;
typedef  TYPE_3__ OptionsContext ;
typedef  TYPE_4__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_DONT_OVERWRITE ; 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,...) ; 
 int check_stream_specifier (TYPE_4__*,TYPE_9__*,char const*) ; 
 int /*<<< orphan*/  exit_program (int) ; 
 int /*<<< orphan*/  parse_meta_type (char*,char*,int*,char const**) ; 

__attribute__((used)) static int copy_metadata(char *outspec, char *inspec, AVFormatContext *oc, AVFormatContext *ic, OptionsContext *o)
{
    AVDictionary **meta_in = NULL;
    AVDictionary **meta_out = NULL;
    int i, ret = 0;
    char type_in, type_out;
    const char *istream_spec = NULL, *ostream_spec = NULL;
    int idx_in = 0, idx_out = 0;

    parse_meta_type(inspec,  &type_in,  &idx_in,  &istream_spec);
    parse_meta_type(outspec, &type_out, &idx_out, &ostream_spec);

    if (!ic) {
        if (type_out == 'g' || !*outspec)
            o->metadata_global_manual = 1;
        if (type_out == 's' || !*outspec)
            o->metadata_streams_manual = 1;
        if (type_out == 'c' || !*outspec)
            o->metadata_chapters_manual = 1;
        return 0;
    }

    if (type_in == 'g' || type_out == 'g')
        o->metadata_global_manual = 1;
    if (type_in == 's' || type_out == 's')
        o->metadata_streams_manual = 1;
    if (type_in == 'c' || type_out == 'c')
        o->metadata_chapters_manual = 1;

    /* ic is NULL when just disabling automatic mappings */
    if (!ic)
        return 0;

#define METADATA_CHECK_INDEX(index, nb_elems, desc)\
    if ((index) < 0 || (index) >= (nb_elems)) {\
        av_log(NULL, AV_LOG_FATAL, "Invalid %s index %d while processing metadata maps.\n",\
                (desc), (index));\
        exit_program(1);\
    }

#define SET_DICT(type, meta, context, index)\
        switch (type) {\
        case 'g':\
            meta = &context->metadata;\
            break;\
        case 'c':\
            METADATA_CHECK_INDEX(index, context->nb_chapters, "chapter")\
            meta = &context->chapters[index]->metadata;\
            break;\
        case 'p':\
            METADATA_CHECK_INDEX(index, context->nb_programs, "program")\
            meta = &context->programs[index]->metadata;\
            break;\
        case 's':\
            break; /* handled separately below */ \
        default: av_assert0(0);\
        }\

    SET_DICT(type_in, meta_in, ic, idx_in);
    SET_DICT(type_out, meta_out, oc, idx_out);

    /* for input streams choose first matching stream */
    if (type_in == 's') {
        for (i = 0; i < ic->nb_streams; i++) {
            if ((ret = check_stream_specifier(ic, ic->streams[i], istream_spec)) > 0) {
                meta_in = &ic->streams[i]->metadata;
                break;
            } else if (ret < 0)
                exit_program(1);
        }
        if (!meta_in) {
            av_log(NULL, AV_LOG_FATAL, "Stream specifier %s does not match  any streams.\n", istream_spec);
            exit_program(1);
        }
    }

    if (type_out == 's') {
        for (i = 0; i < oc->nb_streams; i++) {
            if ((ret = check_stream_specifier(oc, oc->streams[i], ostream_spec)) > 0) {
                meta_out = &oc->streams[i]->metadata;
                av_dict_copy(meta_out, *meta_in, AV_DICT_DONT_OVERWRITE);
            } else if (ret < 0)
                exit_program(1);
        }
    } else
        av_dict_copy(meta_out, *meta_in, AV_DICT_DONT_OVERWRITE);

    return 0;
}