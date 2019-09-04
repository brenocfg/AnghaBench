#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  value; } ;
struct TYPE_18__ {int nb_streams; int /*<<< orphan*/  metadata; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_17__ {int /*<<< orphan*/  metadata; } ;
struct TYPE_16__ {scalar_t__ track_instance_count; } ;
struct TYPE_15__ {int instance; struct TYPE_15__* ref; void* type; int /*<<< orphan*/  name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ MXFPackage ;
typedef  TYPE_2__ MXFContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVDictionaryEntry ;

/* Variables and functions */
 void* MaterialPackage ; 
 void* SourcePackage ; 
 TYPE_5__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxf_write_content_storage (TYPE_4__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mxf_write_essence_container_data (TYPE_4__*) ; 
 int /*<<< orphan*/  mxf_write_identification (TYPE_4__*) ; 
 int /*<<< orphan*/  mxf_write_package (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mxf_write_preface (TYPE_4__*) ; 

__attribute__((used)) static int mxf_write_header_metadata_sets(AVFormatContext *s)
{
    MXFContext *mxf = s->priv_data;
    AVDictionaryEntry *entry = NULL;
    AVStream *st = NULL;
    int i;
    MXFPackage packages[3] = {{0}};
    int package_count = 2;
    packages[0].type = MaterialPackage;
    packages[1].type = SourcePackage;
    packages[1].instance = 1;
    packages[0].ref = &packages[1];


    if (entry = av_dict_get(s->metadata, "material_package_name", NULL, 0))
       packages[0].name = entry->value;

    if (entry = av_dict_get(s->metadata, "file_package_name", NULL, 0)) {
        packages[1].name = entry->value;
    } else {
        /* check if any of the streams contain a file_package_name */
        for (i = 0; i < s->nb_streams; i++) {
            st = s->streams[i];
            if (entry = av_dict_get(st->metadata, "file_package_name", NULL, 0)) {
                packages[1].name = entry->value;
                break;
            }
        }
    }

    entry = av_dict_get(s->metadata, "reel_name", NULL, 0);
    if (entry) {
        packages[2].name = entry->value;
        packages[2].type = SourcePackage;
        packages[2].instance = 2;
        packages[1].ref = &packages[2];
        package_count = 3;
    }

    mxf_write_preface(s);
    mxf_write_identification(s);
    mxf_write_content_storage(s, packages, package_count);
    mxf->track_instance_count = 0;
    for (i = 0; i < package_count; i++)
        mxf_write_package(s, &packages[i]);
    mxf_write_essence_container_data(s);
    return 0;
}