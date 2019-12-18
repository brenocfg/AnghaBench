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
struct TYPE_4__ {int /*<<< orphan*/  (* DrawText ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  LPRECT ;
typedef  int /*<<< orphan*/  LPD3DXSPRITE ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  TYPE_2__ ID3DXFont ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  D3DCOLOR ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void d3d9x_font_draw_text(void *data, void *sprite_data, void *string_data,
      unsigned count, void *rect_data, unsigned format, unsigned color)
{
#ifdef HAVE_D3DX
   ID3DXFont *font = (ID3DXFont*)data;
   if (font)
      font->lpVtbl->DrawText(font, (LPD3DXSPRITE)sprite_data,
            (LPCTSTR)string_data, count, (LPRECT)rect_data,
            (DWORD)format, (D3DCOLOR)color);
#endif
}