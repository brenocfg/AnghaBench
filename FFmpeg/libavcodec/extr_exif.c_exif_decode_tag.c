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
typedef  enum TiffTypes { ____Placeholder_TiffTypes } TiffTypes ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_malloc (int) ; 
 int /*<<< orphan*/  bytestream2_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_tell (int /*<<< orphan*/ *) ; 
 int exif_add_metadata (void*,unsigned int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 char* exif_get_tag_name (unsigned int) ; 
 int ff_exif_decode_ifd (void*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 int ff_tis_ifd (unsigned int) ; 
 int /*<<< orphan*/  ff_tread_tag (int /*<<< orphan*/ *,int,unsigned int*,int*,unsigned int*,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static int exif_decode_tag(void *logctx, GetByteContext *gbytes, int le,
                           int depth, AVDictionary **metadata)
{
    int ret, cur_pos;
    unsigned id, count;
    enum TiffTypes type;

    if (depth > 2) {
        return 0;
    }

    ff_tread_tag(gbytes, le, &id, &type, &count, &cur_pos);

    if (!bytestream2_tell(gbytes)) {
        bytestream2_seek(gbytes, cur_pos, SEEK_SET);
        return 0;
    }

    // read count values and add it metadata
    // store metadata or proceed with next IFD
    ret = ff_tis_ifd(id);
    if (ret) {
        ret = ff_exif_decode_ifd(logctx, gbytes, le, depth + 1, metadata);
    } else {
        const char *name = exif_get_tag_name(id);
        char *use_name   = (char*) name;

        if (!use_name) {
            use_name = av_malloc(7);
            if (!use_name) {
                return AVERROR(ENOMEM);
            }
            snprintf(use_name, 7, "0x%04X", id);
        }

        ret = exif_add_metadata(logctx, count, type, use_name, NULL,
                                gbytes, le, metadata);

        if (!name) {
            av_freep(&use_name);
        }
    }

    bytestream2_seek(gbytes, cur_pos, SEEK_SET);

    return ret;
}