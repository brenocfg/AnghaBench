#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * Data4; int /*<<< orphan*/  Data3; int /*<<< orphan*/  Data2; scalar_t__ Data1; } ;
typedef  TYPE_1__ GUID ;
typedef  int /*<<< orphan*/  FFDXVASharedContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/ * DXVA_SHARED_CONTEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void dxva_list_guids_debug(AVCodecContext *avctx, void *service,
                                 unsigned guid_count, const GUID *guid_list)
{
    FFDXVASharedContext *sctx = DXVA_SHARED_CONTEXT(avctx);
    int i;

    av_log(avctx, AV_LOG_VERBOSE, "Decoder GUIDs reported as supported:\n");

    for (i = 0; i < guid_count; i++) {
        const GUID *guid = &guid_list[i];

        av_log(avctx, AV_LOG_VERBOSE,
             "{%8.8x-%4.4x-%4.4x-%2.2x%2.2x-%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x}",
             (unsigned) guid->Data1, guid->Data2, guid->Data3,
             guid->Data4[0], guid->Data4[1],
             guid->Data4[2], guid->Data4[3],
             guid->Data4[4], guid->Data4[5],
             guid->Data4[6], guid->Data4[7]);

#if CONFIG_D3D11VA
        if (sctx->pix_fmt == AV_PIX_FMT_D3D11) {
            DXGI_FORMAT format;
            // We don't know the maximum valid DXGI_FORMAT, so use 200 as
            // arbitrary upper bound (that could become outdated).
            for (format = 0; format < 200; format++) {
                if (d3d11va_validate_output(service, *guid, &format))
                    av_log(avctx, AV_LOG_VERBOSE, " %d", (int)format);
            }
        }
#endif
#if CONFIG_DXVA2
        if (sctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD) {
            const D3DFORMAT formats[] = {MKTAG('N', 'V', '1', '2'),
                                         MKTAG('P', '0', '1', '0')};
            int i;
            for (i = 0; i < FF_ARRAY_ELEMS(formats); i++) {
                if (dxva2_validate_output(service, *guid, &formats[i]))
                    av_log(avctx, AV_LOG_VERBOSE, " %d", i);
            }
        }
#endif
        av_log(avctx, AV_LOG_VERBOSE, "\n");
    }
}