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
struct Tracks {int dummy; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 scalar_t__ MKBETAG (char,float,char,char) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_close (int /*<<< orphan*/ *) ; 
 int avio_open2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  read_tfra (struct Tracks*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int write_fragments (struct Tracks*,int,int /*<<< orphan*/ *,char const*,int,int,char const*) ; 

__attribute__((used)) static int read_mfra(struct Tracks *tracks, int start_index,
                     const char *file, int split, int ismf,
                     const char *basename, const char* output_prefix)
{
    int err = 0;
    const char* err_str = "";
    AVIOContext *f = NULL;
    int32_t mfra_size;

    if ((err = avio_open2(&f, file, AVIO_FLAG_READ, NULL, NULL)) < 0)
        goto fail;
    avio_seek(f, avio_size(f) - 4, SEEK_SET);
    mfra_size = avio_rb32(f);
    avio_seek(f, -mfra_size, SEEK_CUR);
    if (avio_rb32(f) != mfra_size) {
        err = AVERROR_INVALIDDATA;
        err_str = "mfra size mismatch";
        goto fail;
    }
    if (avio_rb32(f) != MKBETAG('m', 'f', 'r', 'a')) {
        err = AVERROR_INVALIDDATA;
        err_str = "mfra tag mismatch";
        goto fail;
    }
    while (!read_tfra(tracks, start_index, f)) {
        /* Empty */
    }

    if (split || ismf)
        err = write_fragments(tracks, start_index, f, basename, split, ismf,
                              output_prefix);
    err_str = "error in write_fragments";

fail:
    if (f)
        avio_close(f);
    if (err)
        fprintf(stderr, "Unable to read the MFRA atom in %s (%s)\n", file, err_str);
    return err;
}