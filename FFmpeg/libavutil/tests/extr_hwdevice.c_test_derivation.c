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
typedef  enum AVHWDeviceType { ____Placeholder_AVHWDeviceType } AVHWDeviceType ;
struct TYPE_8__ {scalar_t__ data; } ;
struct TYPE_7__ {int type; } ;
typedef  TYPE_1__ AVHWDeviceContext ;
typedef  TYPE_2__ AVBufferRef ;

/* Variables and functions */
 int AV_HWDEVICE_TYPE_NONE ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_2__**) ; 
 int av_hwdevice_ctx_create_derived (TYPE_2__**,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* av_hwdevice_get_type_name (int) ; 
 int av_hwdevice_iterate_types (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int test_derivation(AVBufferRef *src_ref, const char *src_name)
{
    enum AVHWDeviceType derived_type;
    const char *derived_name;
    AVBufferRef *derived_ref = NULL, *back_ref = NULL;
    AVHWDeviceContext *src_dev, *derived_dev;
    int err;

    src_dev = (AVHWDeviceContext*)src_ref->data;

    derived_type = AV_HWDEVICE_TYPE_NONE;
    while (1) {
        derived_type = av_hwdevice_iterate_types(derived_type);
        if (derived_type == AV_HWDEVICE_TYPE_NONE)
            break;

        derived_name = av_hwdevice_get_type_name(derived_type);

        err = av_hwdevice_ctx_create_derived(&derived_ref, derived_type,
                                             src_ref, 0);
        if (err < 0) {
            fprintf(stderr, "Unable to derive %s -> %s: %d.\n",
                    src_name, derived_name, err);
            continue;
        }

        derived_dev = (AVHWDeviceContext*)derived_ref->data;
        if (derived_dev->type != derived_type) {
            fprintf(stderr, "Device derived as type %d has type %d.\n",
                    derived_type, derived_dev->type);
            goto fail;
        }

        if (derived_type == src_dev->type) {
            if (derived_dev != src_dev) {
                fprintf(stderr, "Derivation of %s from itself succeeded "
                        "but did not return the same device.\n", src_name);
                goto fail;
            }
            av_buffer_unref(&derived_ref);
            continue;
        }

        err = av_hwdevice_ctx_create_derived(&back_ref, src_dev->type,
                                             derived_ref, 0);
        if (err < 0) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again failed: %d.\n",
                    src_name, derived_name, err);
            goto fail;
        }

        if (back_ref->data != src_ref->data) {
            fprintf(stderr, "Derivation %s to %s succeeded, but derivation "
                    "back again did not return the original device.\n",
                   src_name, derived_name);
            goto fail;
        }

        fprintf(stderr, "Successfully tested derivation %s -> %s.\n",
                src_name, derived_name);

        av_buffer_unref(&derived_ref);
        av_buffer_unref(&back_ref);
    }

    return 0;

fail:
    av_buffer_unref(&derived_ref);
    av_buffer_unref(&back_ref);
    return -1;
}