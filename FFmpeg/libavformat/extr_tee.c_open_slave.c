#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_22__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int* stream_map; int header_written; TYPE_22__** bsfs; TYPE_3__* avf; int /*<<< orphan*/  use_fifo; int /*<<< orphan*/ * fifo_options; } ;
typedef  TYPE_1__ TeeSlave ;
struct TYPE_29__ {char* key; char* value; } ;
struct TYPE_28__ {int nb_streams; TYPE_2__** streams; int /*<<< orphan*/  strict_std_compliance; int /*<<< orphan*/  flags; int /*<<< orphan*/  interrupt_callback; int /*<<< orphan*/  io_close; int /*<<< orphan*/  io_open; int /*<<< orphan*/  opaque; int /*<<< orphan*/  metadata; } ;
struct TYPE_27__ {int /*<<< orphan*/  codecpar; int /*<<< orphan*/  time_base; } ;
struct TYPE_26__ {int /*<<< orphan*/  par_in; int /*<<< orphan*/  time_base_in; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_OPTION_NOT_FOUND ; 
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  STEAL_OPTION (char*,char*) ; 
 int av_bsf_get_null_filter (TYPE_22__**) ; 
 int av_bsf_init (TYPE_22__*) ; 
 int av_bsf_list_parse_str (char*,TYPE_22__**) ; 
 void* av_calloc (int,int) ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 TYPE_4__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int av_dict_get_string (int /*<<< orphan*/ *,char**,char,char) ; 
 int av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 char* av_err2str (int) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 char* av_strdup (char*) ; 
 char* av_strtok (char*,int /*<<< orphan*/ ,char**) ; 
 int avcodec_parameters_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avformat_alloc_output_context2 (TYPE_3__**,int /*<<< orphan*/ *,char*,char*) ; 
 int avformat_match_stream_specifier (TYPE_3__*,TYPE_2__*,char const*) ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int avformat_write_header (TYPE_3__*,int /*<<< orphan*/ **) ; 
 int ff_format_output_open (TYPE_3__*,char*,int /*<<< orphan*/ *) ; 
 int ff_stream_encode_params_copy (TYPE_2__*,TYPE_2__*) ; 
 int ff_tee_parse_slave_options (TYPE_3__*,char*,int /*<<< orphan*/ **,char**) ; 
 int parse_slave_failure_policy_option (char*,TYPE_1__*) ; 
 int parse_slave_fifo_options (char*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  slave_bsfs_spec_sep ; 
 int /*<<< orphan*/  slave_select_sep ; 
 int strspn (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int open_slave(AVFormatContext *avf, char *slave, TeeSlave *tee_slave)
{
    int i, ret;
    AVDictionary *options = NULL, *bsf_options = NULL;
    AVDictionaryEntry *entry;
    char *filename;
    char *format = NULL, *select = NULL, *on_fail = NULL;
    char *use_fifo = NULL, *fifo_options_str = NULL;
    AVFormatContext *avf2 = NULL;
    AVStream *st, *st2;
    int stream_count;
    int fullret;
    char *subselect = NULL, *next_subselect = NULL, *first_subselect = NULL, *tmp_select = NULL;

    if ((ret = ff_tee_parse_slave_options(avf, slave, &options, &filename)) < 0)
        return ret;

#define STEAL_OPTION(option, field) do {                                \
        if ((entry = av_dict_get(options, option, NULL, 0))) {          \
            field = entry->value;                                       \
            entry->value = NULL; /* prevent it from being freed */      \
            av_dict_set(&options, option, NULL, 0);                     \
        }                                                               \
    } while (0)

    STEAL_OPTION("f", format);
    STEAL_OPTION("select", select);
    STEAL_OPTION("onfail", on_fail);
    STEAL_OPTION("use_fifo", use_fifo);
    STEAL_OPTION("fifo_options", fifo_options_str);
    entry = NULL;
    while ((entry = av_dict_get(options, "bsfs", entry, AV_DICT_IGNORE_SUFFIX))) {
        /* trim out strlen("bsfs") characters from key */
        av_dict_set(&bsf_options, entry->key + 4, entry->value, 0);
        av_dict_set(&options, entry->key, NULL, 0);
    }

    ret = parse_slave_failure_policy_option(on_fail, tee_slave);
    if (ret < 0) {
        av_log(avf, AV_LOG_ERROR,
               "Invalid onfail option value, valid options are 'abort' and 'ignore'\n");
        goto end;
    }

    ret = parse_slave_fifo_options(use_fifo, fifo_options_str, tee_slave);
    if (ret < 0) {
        av_log(avf, AV_LOG_ERROR, "Error parsing fifo options: %s\n", av_err2str(ret));
        goto end;
    }

    if (tee_slave->use_fifo) {

        if (options) {
            char *format_options_str = NULL;
            ret = av_dict_get_string(options, &format_options_str, '=', ':');
            if (ret < 0)
                goto end;

            ret = av_dict_set(&tee_slave->fifo_options, "format_opts", format_options_str,
                              AV_DICT_DONT_STRDUP_VAL);
            if (ret < 0)
                goto end;
        }

        if (format) {
            ret = av_dict_set(&tee_slave->fifo_options, "fifo_format", format,
                              AV_DICT_DONT_STRDUP_VAL);
            format = NULL;
            if (ret < 0)
                goto end;
        }

        av_dict_free(&options);
        options = tee_slave->fifo_options;
    }
    ret = avformat_alloc_output_context2(&avf2, NULL,
                                         tee_slave->use_fifo ? "fifo" :format, filename);
    if (ret < 0)
        goto end;
    tee_slave->avf = avf2;
    av_dict_copy(&avf2->metadata, avf->metadata, 0);
    avf2->opaque   = avf->opaque;
    avf2->io_open  = avf->io_open;
    avf2->io_close = avf->io_close;
    avf2->interrupt_callback = avf->interrupt_callback;
    avf2->flags = avf->flags;
    avf2->strict_std_compliance = avf->strict_std_compliance;

    tee_slave->stream_map = av_calloc(avf->nb_streams, sizeof(*tee_slave->stream_map));
    if (!tee_slave->stream_map) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    stream_count = 0;
    for (i = 0; i < avf->nb_streams; i++) {
        st = avf->streams[i];
        if (select) {
            tmp_select = av_strdup(select);  // av_strtok is destructive so we regenerate it in each loop
            if (!tmp_select) {
                ret = AVERROR(ENOMEM);
                goto end;
            }
            fullret = 0;
            first_subselect = tmp_select;
            next_subselect = NULL;
            while (subselect = av_strtok(first_subselect, slave_select_sep, &next_subselect)) {
                first_subselect = NULL;

                ret = avformat_match_stream_specifier(avf, avf->streams[i], subselect);
                if (ret < 0) {
                    av_log(avf, AV_LOG_ERROR,
                           "Invalid stream specifier '%s' for output '%s'\n",
                           subselect, slave);
                    goto end;
                }
                if (ret != 0) {
                    fullret = 1; // match
                    break;
                }
            }
            av_freep(&tmp_select);

            if (fullret == 0) { /* no match */
                tee_slave->stream_map[i] = -1;
                continue;
            }
        }
        tee_slave->stream_map[i] = stream_count++;

        if (!(st2 = avformat_new_stream(avf2, NULL))) {
            ret = AVERROR(ENOMEM);
            goto end;
        }

        ret = ff_stream_encode_params_copy(st2, st);
        if (ret < 0)
            goto end;
    }

    ret = ff_format_output_open(avf2, filename, NULL);
    if (ret < 0) {
        av_log(avf, AV_LOG_ERROR, "Slave '%s': error opening: %s\n", slave,
               av_err2str(ret));
        goto end;
    }

    if ((ret = avformat_write_header(avf2, &options)) < 0) {
        av_log(avf, AV_LOG_ERROR, "Slave '%s': error writing header: %s\n",
               slave, av_err2str(ret));
        goto end;
    }
    tee_slave->header_written = 1;

    tee_slave->bsfs = av_calloc(avf2->nb_streams, sizeof(*tee_slave->bsfs));
    if (!tee_slave->bsfs) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    entry = NULL;
    while (entry = av_dict_get(bsf_options, "", NULL, AV_DICT_IGNORE_SUFFIX)) {
        const char *spec = entry->key;
        if (*spec) {
            if (strspn(spec, slave_bsfs_spec_sep) != 1) {
                av_log(avf, AV_LOG_ERROR,
                       "Specifier separator in '%s' is '%c', but only characters '%s' "
                       "are allowed\n", entry->key, *spec, slave_bsfs_spec_sep);
                ret = AVERROR(EINVAL);
                goto end;
            }
            spec++; /* consume separator */
        }

        for (i = 0; i < avf2->nb_streams; i++) {
            ret = avformat_match_stream_specifier(avf2, avf2->streams[i], spec);
            if (ret < 0) {
                av_log(avf, AV_LOG_ERROR,
                       "Invalid stream specifier '%s' in bsfs option '%s' for slave "
                       "output '%s'\n", spec, entry->key, filename);
                goto end;
            }

            if (ret > 0) {
                av_log(avf, AV_LOG_DEBUG, "spec:%s bsfs:%s matches stream %d of slave "
                       "output '%s'\n", spec, entry->value, i, filename);
                if (tee_slave->bsfs[i]) {
                    av_log(avf, AV_LOG_WARNING,
                           "Duplicate bsfs specification associated to stream %d of slave "
                           "output '%s', filters will be ignored\n", i, filename);
                    continue;
                }
                ret = av_bsf_list_parse_str(entry->value, &tee_slave->bsfs[i]);
                if (ret < 0) {
                    av_log(avf, AV_LOG_ERROR,
                           "Error parsing bitstream filter sequence '%s' associated to "
                           "stream %d of slave output '%s'\n", entry->value, i, filename);
                    goto end;
                }
            }
        }

        av_dict_set(&bsf_options, entry->key, NULL, 0);
    }

    for (i = 0; i < avf->nb_streams; i++){
        int target_stream = tee_slave->stream_map[i];
        if (target_stream < 0)
            continue;

        if (!tee_slave->bsfs[target_stream]) {
            /* Add pass-through bitstream filter */
            ret = av_bsf_get_null_filter(&tee_slave->bsfs[target_stream]);
            if (ret < 0) {
                av_log(avf, AV_LOG_ERROR,
                       "Failed to create pass-through bitstream filter: %s\n",
                       av_err2str(ret));
                goto end;
            }
        }

        tee_slave->bsfs[target_stream]->time_base_in = avf->streams[i]->time_base;
        ret = avcodec_parameters_copy(tee_slave->bsfs[target_stream]->par_in,
                                      avf->streams[i]->codecpar);
        if (ret < 0)
            goto end;

        ret = av_bsf_init(tee_slave->bsfs[target_stream]);
        if (ret < 0) {
            av_log(avf, AV_LOG_ERROR,
            "Failed to initialize bitstream filter(s): %s\n",
            av_err2str(ret));
            goto end;
        }
    }

    if (options) {
        entry = NULL;
        while ((entry = av_dict_get(options, "", entry, AV_DICT_IGNORE_SUFFIX)))
            av_log(avf2, AV_LOG_ERROR, "Unknown option '%s'\n", entry->key);
        ret = AVERROR_OPTION_NOT_FOUND;
        goto end;
    }

end:
    av_free(format);
    av_free(select);
    av_free(on_fail);
    av_dict_free(&options);
    av_dict_free(&bsf_options);
    av_freep(&tmp_select);
    return ret;
}