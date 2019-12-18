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
struct TYPE_4__ {int cbSize; int style; char const* lpszClassName; scalar_t__ hbrBackground; scalar_t__ hIconSm; int /*<<< orphan*/  hIcon; int /*<<< orphan*/  hCursor; int /*<<< orphan*/  hInstance; } ;
typedef  TYPE_1__ WNDCLASSEX ;
typedef  scalar_t__ HICON ;
typedef  scalar_t__ HBRUSH ;

/* Variables and functions */
 scalar_t__ COLOR_WINDOW ; 
 int CS_CLASSDC ; 
 int CS_HREDRAW ; 
 int CS_OWNDC ; 
 int CS_VREDRAW ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDC_ARROW ; 
 int /*<<< orphan*/  IDI_ICON ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 int /*<<< orphan*/  LoadCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadIcon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LoadImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_HASH_USER_LANGUAGE ; 
 int /*<<< orphan*/  MSG_PROGRAM ; 
 int /*<<< orphan*/  RegisterClassEx (TYPE_1__*) ; 
 int /*<<< orphan*/  SetThreadUILanguage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * msg_hash_get_uint (int /*<<< orphan*/ ) ; 
 char const* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win32_get_langid_from_retro_lang (int /*<<< orphan*/ ) ; 

bool win32_window_init(WNDCLASSEX *wndclass,
      bool fullscreen, const char *class_name)
{
#if _WIN32_WINNT >= 0x0501
   /* Use the language set in the config for the menubar... also changes the console language. */
   SetThreadUILanguage(win32_get_langid_from_retro_lang(*msg_hash_get_uint(MSG_HASH_USER_LANGUAGE)));
#endif
   wndclass->cbSize        = sizeof(WNDCLASSEX);
   wndclass->style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
   wndclass->hInstance     = GetModuleHandle(NULL);
   wndclass->hCursor       = LoadCursor(NULL, IDC_ARROW);
   wndclass->lpszClassName = (class_name != NULL) ? class_name : msg_hash_to_str(MSG_PROGRAM);
   wndclass->hIcon         = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
   wndclass->hIconSm       = (HICON)LoadImage(GetModuleHandle(NULL),
         MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 16, 16, 0);
   if (!fullscreen)
      wndclass->hbrBackground = (HBRUSH)COLOR_WINDOW;

   if (class_name != NULL)
      wndclass->style         |= CS_CLASSDC;

   if (!RegisterClassEx(wndclass))
      return false;

   return true;
}