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
typedef  int /*<<< orphan*/  ii ;
typedef  int /*<<< orphan*/  bi ;
struct TYPE_8__ {unsigned char* pixels; int width; int height; } ;
struct TYPE_7__ {int bV5Size; int bV5Width; int bV5Height; int bV5Planes; int bV5BitCount; int bV5RedMask; int bV5GreenMask; int bV5BlueMask; int bV5AlphaMask; int xHotspot; int yHotspot; void* hbmColor; void* hbmMask; scalar_t__ fIcon; int /*<<< orphan*/  bV5Compression; } ;
typedef  TYPE_1__ ICONINFO ;
typedef  int /*<<< orphan*/ * HICON ;
typedef  int /*<<< orphan*/  HDC ;
typedef  void* HBITMAP ;
typedef  TYPE_2__ GLFWimage ;
typedef  scalar_t__ GLFWbool ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ BITMAPV5HEADER ;
typedef  int /*<<< orphan*/  BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_BITFIELDS ; 
 void* CreateBitmap (int,int,int,int,int /*<<< orphan*/ *) ; 
 void* CreateDIBSection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateIconIndirect (TYPE_1__*) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteObject (void*) ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static HICON createIcon(const GLFWimage* image,
                        int xhot, int yhot, GLFWbool icon)
{
    int i;
    HDC dc;
    HICON handle;
    HBITMAP color, mask;
    BITMAPV5HEADER bi;
    ICONINFO ii;
    unsigned char* target = NULL;
    unsigned char* source = image->pixels;

    ZeroMemory(&bi, sizeof(bi));
    bi.bV5Size        = sizeof(BITMAPV5HEADER);
    bi.bV5Width       = image->width;
    bi.bV5Height      = -image->height;
    bi.bV5Planes      = 1;
    bi.bV5BitCount    = 32;
    bi.bV5Compression = BI_BITFIELDS;
    bi.bV5RedMask     = 0x00ff0000;
    bi.bV5GreenMask   = 0x0000ff00;
    bi.bV5BlueMask    = 0x000000ff;
    bi.bV5AlphaMask   = 0xff000000;

    dc = GetDC(NULL);
    color = CreateDIBSection(dc,
                             (BITMAPINFO*) &bi,
                             DIB_RGB_COLORS,
                             (void**) &target,
                             NULL,
                             (DWORD) 0);
    ReleaseDC(NULL, dc);

    if (!color)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Win32: Failed to create RGBA bitmap");
        return NULL;
    }

    mask = CreateBitmap(image->width, image->height, 1, 1, NULL);
    if (!mask)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Win32: Failed to create mask bitmap");
        DeleteObject(color);
        return NULL;
    }

    for (i = 0;  i < image->width * image->height;  i++)
    {
        target[0] = source[2];
        target[1] = source[1];
        target[2] = source[0];
        target[3] = source[3];
        target += 4;
        source += 4;
    }

    ZeroMemory(&ii, sizeof(ii));
    ii.fIcon    = icon;
    ii.xHotspot = xhot;
    ii.yHotspot = yhot;
    ii.hbmMask  = mask;
    ii.hbmColor = color;

    handle = CreateIconIndirect(&ii);

    DeleteObject(color);
    DeleteObject(mask);

    if (!handle)
    {
        if (icon)
            _glfwInputError(GLFW_PLATFORM_ERROR, "Win32: Failed to create icon");
        else
            _glfwInputError(GLFW_PLATFORM_ERROR, "Win32: Failed to create cursor");
    }

    return handle;
}