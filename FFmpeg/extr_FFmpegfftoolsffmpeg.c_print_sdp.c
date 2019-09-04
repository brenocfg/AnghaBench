#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sdp ;
struct TYPE_12__ {TYPE_2__* ctx; int /*<<< orphan*/  header_written; } ;
struct TYPE_11__ {TYPE_1__* oformat; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_freep (TYPE_2__***) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_2__**) ; 
 TYPE_2__** av_malloc_array (int,int) ; 
 int /*<<< orphan*/  av_sdp_create (TYPE_2__**,int,char*,int) ; 
 int /*<<< orphan*/  avio_closep (int /*<<< orphan*/ **) ; 
 scalar_t__ avio_open2 (int /*<<< orphan*/ **,TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  exit_program (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_cb ; 
 int nb_output_files ; 
 TYPE_4__** output_files ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 TYPE_2__** sdp_filename ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void print_sdp(void)
{
    char sdp[16384];
    int i;
    int j;
    AVIOContext *sdp_pb;
    AVFormatContext **avc;

    for (i = 0; i < nb_output_files; i++) {
        if (!output_files[i]->header_written)
            return;
    }

    avc = av_malloc_array(nb_output_files, sizeof(*avc));
    if (!avc)
        exit_program(1);
    for (i = 0, j = 0; i < nb_output_files; i++) {
        if (!strcmp(output_files[i]->ctx->oformat->name, "rtp")) {
            avc[j] = output_files[i]->ctx;
            j++;
        }
    }

    if (!j)
        goto fail;

    av_sdp_create(avc, j, sdp, sizeof(sdp));

    if (!sdp_filename) {
        printf("SDP:\n%s\n", sdp);
        fflush(stdout);
    } else {
        if (avio_open2(&sdp_pb, sdp_filename, AVIO_FLAG_WRITE, &int_cb, NULL) < 0) {
            av_log(NULL, AV_LOG_ERROR, "Failed to open sdp file '%s'\n", sdp_filename);
        } else {
            avio_printf(sdp_pb, "SDP:\n%s", sdp);
            avio_closep(&sdp_pb);
            av_freep(&sdp_filename);
        }
    }

fail:
    av_freep(&avc);
}