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
typedef  int /*<<< orphan*/  filename ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int nb_inputs; scalar_t__ format; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  StreamContext ;
typedef  TYPE_1__ SignatureContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ FORMAT_XML ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 scalar_t__ av_get_frame_filename (char*,int,int /*<<< orphan*/ ,int) ; 
 int av_strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int binary_export (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 int xml_export (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int export(AVFilterContext *ctx, StreamContext *sc, int input)
{
    SignatureContext* sic = ctx->priv;
    char filename[1024];

    if (sic->nb_inputs > 1) {
        /* error already handled */
        av_assert0(av_get_frame_filename(filename, sizeof(filename), sic->filename, input) == 0);
    } else {
        if (av_strlcpy(filename, sic->filename, sizeof(filename)) >= sizeof(filename))
            return AVERROR(EINVAL);
    }
    if (sic->format == FORMAT_XML) {
        return xml_export(ctx, sc, filename);
    } else {
        return binary_export(ctx, sc, filename);
    }
}