#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int extradata_size; int /*<<< orphan*/  extradata; scalar_t__ priv_data; } ;
typedef  int /*<<< orphan*/  DVDSubContext ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_malloc (int) ; 
 int ff_set_dimensions (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_palette (int /*<<< orphan*/ *,char*) ; 
 int sscanf (char*,char*,int*,int*) ; 
 int strcspn (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strspn (char*,char*) ; 

__attribute__((used)) static int dvdsub_parse_extradata(AVCodecContext *avctx)
{
    DVDSubContext *ctx = (DVDSubContext*) avctx->priv_data;
    char *dataorig, *data;
    int ret = 1;

    if (!avctx->extradata || !avctx->extradata_size)
        return 1;

    dataorig = data = av_malloc(avctx->extradata_size+1);
    if (!data)
        return AVERROR(ENOMEM);
    memcpy(data, avctx->extradata, avctx->extradata_size);
    data[avctx->extradata_size] = '\0';

    for(;;) {
        int pos = strcspn(data, "\n\r");
        if (pos==0 && *data==0)
            break;

        if (strncmp("palette:", data, 8) == 0) {
            parse_palette(ctx, data + 8);
        } else if (strncmp("size:", data, 5) == 0) {
            int w, h;
            if (sscanf(data + 5, "%dx%d", &w, &h) == 2) {
               ret = ff_set_dimensions(avctx, w, h);
               if (ret < 0)
                   goto fail;
            }
        }

        data += pos;
        data += strspn(data, "\n\r");
    }

fail:
    av_free(dataorig);
    return ret;
}