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
struct TYPE_5__ {TYPE_1__* lpVtbl; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* GetTextMetrics ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  TEXTMETRICA ;
typedef  TYPE_2__ ID3DXFont ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

void d3d9x_font_get_text_metrics(void *data, void *metrics)
{
#ifdef HAVE_D3DX
   ID3DXFont *font = (ID3DXFont*)data;
   if (font)
      font->lpVtbl->GetTextMetrics(font, (TEXTMETRICA*)metrics);
#endif
}