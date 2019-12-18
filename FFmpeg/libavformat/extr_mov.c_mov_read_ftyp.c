#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  metadata; } ;
struct TYPE_7__ {int size; } ;
struct TYPE_6__ {int isom; TYPE_5__* fc; } ;
typedef  TYPE_1__ MOVContext ;
typedef  TYPE_2__ MOVAtom ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,char*) ; 
 char* av_malloc (int) ; 
 int /*<<< orphan*/  avio_rb32 (int /*<<< orphan*/ *) ; 
 int ffio_read_size (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int mov_read_ftyp(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    uint32_t minor_ver;
    int comp_brand_size;
    char* comp_brands_str;
    uint8_t type[5] = {0};
    int ret = ffio_read_size(pb, type, 4);
    if (ret < 0)
        return ret;

    if (strcmp(type, "qt  "))
        c->isom = 1;
    av_log(c->fc, AV_LOG_DEBUG, "ISO: File Type Major Brand: %.4s\n",(char *)&type);
    av_dict_set(&c->fc->metadata, "major_brand", type, 0);
    minor_ver = avio_rb32(pb); /* minor version */
    av_dict_set_int(&c->fc->metadata, "minor_version", minor_ver, 0);

    comp_brand_size = atom.size - 8;
    if (comp_brand_size < 0)
        return AVERROR_INVALIDDATA;
    comp_brands_str = av_malloc(comp_brand_size + 1); /* Add null terminator */
    if (!comp_brands_str)
        return AVERROR(ENOMEM);

    ret = ffio_read_size(pb, comp_brands_str, comp_brand_size);
    if (ret < 0) {
        av_freep(&comp_brands_str);
        return ret;
    }
    comp_brands_str[comp_brand_size] = 0;
    av_dict_set(&c->fc->metadata, "compatible_brands", comp_brands_str, 0);
    av_freep(&comp_brands_str);

    return 0;
}