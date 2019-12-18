#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bih ;
struct TYPE_4__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int /*<<< orphan*/  biCompression; } ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  TYPE_1__ BITMAPINFOHEADER ;
typedef  int /*<<< orphan*/  BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  CBM_INIT ; 
 int /*<<< orphan*/ * CreateDIBitmap (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrameWnd ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  READPNG_24 ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  lprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int readpng (void*,char const*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static HBITMAP png2hb(const char *fname, int is_480)
{
  BITMAPINFOHEADER bih;
  HBITMAP bmp;
  void *bmem;
  int ret;

  bmem = calloc(1, is_480 ? 480*240*3 : 320*240*3);
  if (bmem == NULL) return NULL;
  ret = readpng(bmem, fname, READPNG_24, is_480 ? 480 : 320, 240);
  if (ret != 0) {
    free(bmem);
    return NULL;
  }

  memset(&bih, 0, sizeof(bih));
  bih.biSize = sizeof(bih);
  bih.biWidth = is_480 ? 480 : 320;
  bih.biHeight = -240;
  bih.biPlanes = 1;
  bih.biBitCount = 24;
  bih.biCompression = BI_RGB;
  bmp = CreateDIBitmap(GetDC(FrameWnd), &bih, CBM_INIT, bmem, (BITMAPINFO *)&bih, 0);
  if (bmp == NULL)
    lprintf("CreateDIBitmap failed with %i", GetLastError());

  free(bmem);
  return bmp;
}