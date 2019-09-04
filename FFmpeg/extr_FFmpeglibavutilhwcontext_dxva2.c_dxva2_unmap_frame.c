#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  priv; TYPE_1__* source; } ;
struct TYPE_4__ {scalar_t__* data; } ;
typedef  int /*<<< orphan*/  IDirect3DSurface9 ;
typedef  TYPE_2__ HWMapDescriptor ;
typedef  int /*<<< orphan*/  AVHWFramesContext ;

/* Variables and functions */
 int /*<<< orphan*/  IDirect3DSurface9_UnlockRect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dxva2_unmap_frame(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)hwmap->source->data[3];
    IDirect3DSurface9_UnlockRect(surface);
    av_freep(&hwmap->priv);
}