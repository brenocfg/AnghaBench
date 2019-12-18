#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVHWDeviceType { ____Placeholder_AVHWDeviceType } AVHWDeviceType ;
struct TYPE_7__ {scalar_t__ data; } ;
struct TYPE_6__ {int type; } ;
typedef  TYPE_1__ AVHWDeviceContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_2__ AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (TYPE_2__**) ; 
 int av_hwdevice_ctx_create (TYPE_2__**,int,char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int test_derivation (TYPE_2__*,char const*) ; 

__attribute__((used)) static int test_device(enum AVHWDeviceType type, const char *name,
                       const char *device, AVDictionary *opts, int flags)
{
    AVBufferRef *ref;
    AVHWDeviceContext *dev;
    int err;

    err = av_hwdevice_ctx_create(&ref, type, device, opts, flags);
    if (err < 0) {
        fprintf(stderr, "Failed to create %s device: %d.\n", name, err);
        return 1;
    }

    dev = (AVHWDeviceContext*)ref->data;
    if (dev->type != type) {
        fprintf(stderr, "Device created as type %d has type %d.\n",
                type, dev->type);
        av_buffer_unref(&ref);
        return -1;
    }

    fprintf(stderr, "Device type %s successfully created.\n", name);

    err = test_derivation(ref, name);

    av_buffer_unref(&ref);

    return err;
}