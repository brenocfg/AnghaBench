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
struct TYPE_3__ {int Flags; void* lpstrFileTitle; void* lpstrFile; int /*<<< orphan*/  hwndOwner; } ;
typedef  void* PTSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetSaveFileName (TYPE_1__*) ; 
 int OFN_HIDEREADONLY ; 
 int OFN_OVERWRITEPROMPT ; 
 TYPE_1__ ofn ; 

BOOL PngFileSaveDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
    ofn.hwndOwner         = hwnd;
    ofn.lpstrFile         = pstrFileName;
    ofn.lpstrFileTitle    = pstrTitleName;
    ofn.Flags             = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

    return GetSaveFileName (&ofn);
}