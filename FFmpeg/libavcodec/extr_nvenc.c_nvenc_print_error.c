#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* priv_data; } ;
struct TYPE_9__ {char* (* nvEncGetLastErrorString ) (scalar_t__) ;} ;
struct TYPE_7__ {TYPE_3__ nvenc_funcs; } ;
struct TYPE_8__ {scalar_t__ nvencoder; TYPE_1__ nvenc_dload_funcs; } ;
typedef  TYPE_2__ NvencContext ;
typedef  TYPE_3__ NV_ENCODE_API_FUNCTION_LIST ;
typedef  int /*<<< orphan*/  NVENCSTATUS ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ,char const*) ; 
 int nvenc_map_error (int /*<<< orphan*/ ,char const**) ; 
 char* stub1 (scalar_t__) ; 

__attribute__((used)) static int nvenc_print_error(AVCodecContext *avctx, NVENCSTATUS err,
                             const char *error_string)
{
    const char *desc;
    const char *details = "(no details)";
    int ret = nvenc_map_error(err, &desc);

#ifdef NVENC_HAVE_GETLASTERRORSTRING
    NvencContext *ctx = avctx->priv_data;
    NV_ENCODE_API_FUNCTION_LIST *p_nvenc = &ctx->nvenc_dload_funcs.nvenc_funcs;

    if (p_nvenc && ctx->nvencoder)
        details = p_nvenc->nvEncGetLastErrorString(ctx->nvencoder);
#endif

    av_log(avctx, AV_LOG_ERROR, "%s: %s (%d): %s\n", error_string, desc, err, details);

    return ret;
}