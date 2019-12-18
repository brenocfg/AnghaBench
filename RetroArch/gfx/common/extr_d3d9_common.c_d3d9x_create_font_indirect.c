#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ID3DXFont {int dummy; } ;
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE9 ;
typedef  int /*<<< orphan*/  D3DXFONT_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  D3D9CreateFontIndirect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ID3DXFont**) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

bool d3d9x_create_font_indirect(void *_dev,
      void *desc, void **font_data)
{
#ifdef HAVE_D3DX
   LPDIRECT3DDEVICE9 dev = (LPDIRECT3DDEVICE9)_dev;
   if (SUCCEEDED(D3D9CreateFontIndirect(
               dev, (D3DXFONT_DESC*)desc,
               (struct ID3DXFont**)font_data)))
      return true;
#endif

   return false;
}