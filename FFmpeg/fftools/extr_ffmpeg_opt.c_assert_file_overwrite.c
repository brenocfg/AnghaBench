#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* ctx; } ;
struct TYPE_6__ {char* url; TYPE_1__* iformat; } ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_3__ InputFile ;

/* Variables and functions */
 int AVFMT_NOFILE ; 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ avio_check (char const*,int /*<<< orphan*/ ) ; 
 char* avio_find_protocol_name (char const*) ; 
 int /*<<< orphan*/  exit_program (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ file_overwrite ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__** input_files ; 
 int nb_input_files ; 
 scalar_t__ no_file_overwrite ; 
 int /*<<< orphan*/  read_yesno () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stdin_interaction ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  term_exit () ; 
 int /*<<< orphan*/  term_init () ; 

__attribute__((used)) static void assert_file_overwrite(const char *filename)
{
    const char *proto_name = avio_find_protocol_name(filename);

    if (file_overwrite && no_file_overwrite) {
        fprintf(stderr, "Error, both -y and -n supplied. Exiting.\n");
        exit_program(1);
    }

    if (!file_overwrite) {
        if (proto_name && !strcmp(proto_name, "file") && avio_check(filename, 0) == 0) {
            if (stdin_interaction && !no_file_overwrite) {
                fprintf(stderr,"File '%s' already exists. Overwrite? [y/N] ", filename);
                fflush(stderr);
                term_exit();
                signal(SIGINT, SIG_DFL);
                if (!read_yesno()) {
                    av_log(NULL, AV_LOG_FATAL, "Not overwriting - exiting\n");
                    exit_program(1);
                }
                term_init();
            }
            else {
                av_log(NULL, AV_LOG_FATAL, "File '%s' already exists. Exiting.\n", filename);
                exit_program(1);
            }
        }
    }

    if (proto_name && !strcmp(proto_name, "file")) {
        for (int i = 0; i < nb_input_files; i++) {
             InputFile *file = input_files[i];
             if (file->ctx->iformat->flags & AVFMT_NOFILE)
                 continue;
             if (!strcmp(filename, file->ctx->url)) {
                 av_log(NULL, AV_LOG_FATAL, "Output %s same as Input #%d - exiting\n", filename, i);
                 av_log(NULL, AV_LOG_WARNING, "FFmpeg cannot edit existing files in-place.\n");
                 exit_program(1);
             }
        }
    }
}