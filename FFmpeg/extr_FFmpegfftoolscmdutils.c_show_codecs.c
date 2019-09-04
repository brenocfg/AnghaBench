#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {char* name; int props; char* long_name; int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ AVCodecDescriptor ;
typedef  TYPE_2__ AVCodec ;

/* Variables and functions */
 int AV_CODEC_PROP_INTRA_ONLY ; 
 int AV_CODEC_PROP_LOSSLESS ; 
 int AV_CODEC_PROP_LOSSY ; 
 int /*<<< orphan*/  av_free (TYPE_1__ const**) ; 
 scalar_t__ avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 scalar_t__ avcodec_find_encoder (int /*<<< orphan*/ ) ; 
 unsigned int get_codecs_sorted (TYPE_1__ const***) ; 
 int get_media_type_char (int /*<<< orphan*/ ) ; 
 TYPE_2__* next_codec_for_id (int /*<<< orphan*/ ,TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  print_codecs_for_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strstr (char*,char*) ; 

int show_codecs(void *optctx, const char *opt, const char *arg)
{
    const AVCodecDescriptor **codecs;
    unsigned i, nb_codecs = get_codecs_sorted(&codecs);

    printf("Codecs:\n"
           " D..... = Decoding supported\n"
           " .E.... = Encoding supported\n"
           " ..V... = Video codec\n"
           " ..A... = Audio codec\n"
           " ..S... = Subtitle codec\n"
           " ...I.. = Intra frame-only codec\n"
           " ....L. = Lossy compression\n"
           " .....S = Lossless compression\n"
           " -------\n");
    for (i = 0; i < nb_codecs; i++) {
        const AVCodecDescriptor *desc = codecs[i];
        const AVCodec *codec = NULL;

        if (strstr(desc->name, "_deprecated"))
            continue;

        printf(" ");
        printf(avcodec_find_decoder(desc->id) ? "D" : ".");
        printf(avcodec_find_encoder(desc->id) ? "E" : ".");

        printf("%c", get_media_type_char(desc->type));
        printf((desc->props & AV_CODEC_PROP_INTRA_ONLY) ? "I" : ".");
        printf((desc->props & AV_CODEC_PROP_LOSSY)      ? "L" : ".");
        printf((desc->props & AV_CODEC_PROP_LOSSLESS)   ? "S" : ".");

        printf(" %-20s %s", desc->name, desc->long_name ? desc->long_name : "");

        /* print decoders/encoders when there's more than one or their
         * names are different from codec name */
        while ((codec = next_codec_for_id(desc->id, codec, 0))) {
            if (strcmp(codec->name, desc->name)) {
                print_codecs_for_id(desc->id, 0);
                break;
            }
        }
        codec = NULL;
        while ((codec = next_codec_for_id(desc->id, codec, 1))) {
            if (strcmp(codec->name, desc->name)) {
                print_codecs_for_id(desc->id, 1);
                break;
            }
        }

        printf("\n");
    }
    av_free(codecs);
    return 0;
}